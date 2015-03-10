class CreateTags < ActiveRecord::Migration
  def change
    create_table :tags do |t|

      t.timestamps
      t.string		:tag_string
      t.belongs_to	:post, index: true
    end
  end
end
