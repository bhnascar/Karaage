class AddProfileUrlString < ActiveRecord::Migration
  def change
  	add_column :users, :user_profile_url, :string
  end
end
