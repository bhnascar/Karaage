class Tag < ActiveRecord::Base
	belongs_to :post
  validates :tag_string, presence: true
end
