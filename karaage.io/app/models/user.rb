class User < ActiveRecord::Base
	include ActiveModel::ForbiddenAttributesProtection

  require 'securerandom'
  require 'digest/sha1'

  validates :user_first_name, :user_last_name, :user_email, presence: true
  validates :user_email, uniqueness: true
  attr_accessor :user_password

  def pass
    return @password
  end

  def pass=(password)
    self.user_salt = SecureRandom.hex
    self.user_hash = Digest::SHA1.hexdigest(password + self.user_salt)
    @password = password
  end

  def password_valid?(password)
    return self.user_hash == Digest::SHA1.hexdigest(password + self.user_salt).to_s
  end
end
