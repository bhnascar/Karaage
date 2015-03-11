class AddProfileToUser < ActiveRecord::Migration
  def change
  	add_column :users, :user_bio, :string
  end
end
