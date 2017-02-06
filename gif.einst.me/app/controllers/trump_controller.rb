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

    FileUtils.rm_rf gif_file

    #
    cmd = '/bin/bash /home/einst/src/trump-gif/generate ' + 
      "#{page_1_file} #{page_2_file} #{video_file} #{gif_file}"
    puts cmd
    spawn(cmd)

    redirect_to trump_generate_path(uid: params[:uid])
  end

  def generate
    @uid = params[:uid]
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