class CreateTesters < ActiveRecord::Migration
  def change
    create_table :testers do |t|

      t.timestamps
      t.string		:tester_first_name
      t.string		:tester_last_name
      t.string		:tester_email
      t.string		:tester_organization
      t.string		:tester_role
    end
  end
end
