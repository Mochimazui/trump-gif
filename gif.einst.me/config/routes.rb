Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html

  root to: 'trump#index'

  get '/trump/index', to: 'trump#index'
  post '/trump/upload', to: 'trump#upload'
  get '/trump/generate', to: 'trump#generate'
  get '/trump/generate_query', to: 'trump#generate_query'
  get '/trump/recent', to: 'trump#recent'

end
