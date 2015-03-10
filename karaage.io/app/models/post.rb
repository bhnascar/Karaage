class Post < ActiveRecord::Base
	belongs_to :user
	has_many :tags

	validates :post_date, :post_content, :post_is_published, presence: true
	attr_accessor :post_time
end
