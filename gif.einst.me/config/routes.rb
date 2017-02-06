Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html

  root to: 'trump#index'
  get '/trump/index', to: 'trump#index'

end
