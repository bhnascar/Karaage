class User < ActiveRecord::Base
	include ActiveModel::ForbiddenAttributesProtection

  require 'securerandom'
  require 'digest/sha1'

  validates :user_first_name, :user_last_name, :user_email, presence: true
  validates :user_email, uniqueness: true
  attr_accessor :user_password
  validates :user_password, length: {minimum: 8, maximum: 64}

  def password
    return @password
  end

  def password=(password)
    self.user_salt = SecureRandom.hex
    self.user_hash = Digest::SHA1.hexdigest(password + self.user_salt)
    @password = password
  end

  def password_valid?(password)
    return self.user_hash == Digest::SHA1.hexdigest(password + self.user_salt).to_s
  end
end
