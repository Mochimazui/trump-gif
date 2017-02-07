class TrumpController < ApplicationController

  def index
    @uid = SecureRandom.hex
  end

  def upload
    #
    uid = params[:uid]

    if uid.gsub(/\W+/, '') != uid 
      # illegal uid
      redirect_to trump_index_path and return
    end

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

    cmd = '/bin/bash /home/einst/src/trump-gif/generate ' + 
      "#{page_1_file} #{page_2_file} #{video_file} #{gif_file} #{txt_file}"
    spawn(cmd)

    redirect_to trump_generate_path(uid: params[:uid])
  end

  def generate
    @uid = params[:uid]
    if @uid.gsub(/\W+/, '') != @uid 
      redirect_to trump_index_path and return
    end
  end
  
  def generate_query
    uid = params[:uid]
    if uid.gsub(/\W+/, '') != uid 
      render :json => {finished: 0}
      return
    end
    txt_file = Rails.root.join('public', 'gif', uid + '.txt')
    if txt_file.exist?
      render :json => {finished: 1}
    else
      render :json => {finished: 0}
    end
  end

  def recent
    @files = Dir[Rails.root.join('public', 'gif').to_s + '/*'].sort_by{ |f| File.mtime(f) }
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

end
