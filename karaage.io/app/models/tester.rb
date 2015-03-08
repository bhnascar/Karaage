class Tester < ActiveRecord::Base
  validates :tester_first_name, :tester_last_name, :tester_email, presence: true
end
