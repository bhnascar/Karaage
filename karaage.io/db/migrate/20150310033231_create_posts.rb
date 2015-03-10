class CreatePosts < ActiveRecord::Migration
  def change
    create_table :posts do |t|

      t.timestamps
      t.datetime	:post_date
      t.string		:post_title
      t.string		:post_content
      t.integer		:post_is_published
      t.belongs_to	:user, index: true
    end
  end
end
