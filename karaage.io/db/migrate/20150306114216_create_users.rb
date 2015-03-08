class CreateUsers < ActiveRecord::Migration
  def change
    create_table :users do |t|

      t.timestamps
      t.string			:user_first_name
      t.string			:user_last_name
      t.string      :user_email
      t.string			:user_salt
      t.string			:user_hash
      t.string      :user_organization
      t.integer     :user_privileges
    end
  end
end
