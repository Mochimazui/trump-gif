class TrumpController < ApplicationController

  def index
    @uid = SecureRandom.hex
    @options = params[:options] == '1'
  end

  def upload
    #uid = params[:uid]
    #redirect_to trump_index_path and return if !check_uid(uid)
    uid = SecureRandom.hex

    page_1 = params[:page_1]
    page_2 = params[:page_2]

    if !page_1 || !page_2
      redirect_to trump_index_path and return
    end

    dir = Rails.root.join('tmp', 'gif', uid)
    FileUtils.rm_rf dir if dir.exist?
    FileUtils.mkdir_p dir

    page_1_file = save_file(dir, page_1, 'page_1')
    page_2_file = save_file(dir, page_2, 'page_2')
    video_file = Rails.root.join('tmp', 'gif', uid, 'output.avi')
    gif_file = Rails.root.join('public', 'gif', uid + '.gif')
    txt_file = Rails.root.join('public', 'gif', uid + '.txt')

    FileUtils.rm_rf gif_file
    FileUtils.rm_rf txt_file

    colors = get_option(params[:colors], 255, 2, 255)
    compress = get_option(params[:compress], 40, 0, 100)
    width = get_option(params[:width], 250, 100, 400)

    cmd = '/bin/bash /home/einst/src/trump-gif/generate_with_options ' + 
      "#{page_1_file} #{page_2_file} #{video_file} #{colors} #{compress} #{width} #{gif_file} #{txt_file}"
    spawn(cmd)

    #redirect_to trump_generate_path(uid: params[:uid])
    redirect_to trump_generate_path(uid: uid)
  end

  def generate
    @uid = params[:uid]
    redirect_to trump_index_path and return if !check_uid(@uid)
  end
  
  def generate_query
    uid = params[:uid]
    render :json => {finished: 0} and return if !check_uid(uid)
    #
    txt_file = Rails.root.join('public', 'gif', uid + '.txt')
    render :json => {finished: txt_file.exist? ? 1 : 0}
  end

  def recent
    @files = Dir[Rails.root.join('public', 'gif').to_s + '/*.gif'].sort_by{ |f| File.mtime(f) }
    @count = @files.size
    @files = @files.last(10) 
    @files = @files.collect { |f| File.basename(f) }
    @files = @files.reverse
  end

private
  
  def save_file(dir, file, name)
    ext = File.extname(file.original_filename)
    name = dir.join(name + ext)
    File.open(name, 'wb') do |f|
      f.write(file.read)
    end
    return name
  end

  def check_uid(uid)
    return uid.gsub(/\W+/, '') == uid 
  end

  def get_option(input, default, low, high)
    return default if !input
    input = input.to_i
    return low if input < low
    return high if input > high
    return input
  end

end
