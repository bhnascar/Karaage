class HomeController < ApplicationController
	def index

	end

  def mailing
    @tester = Tester.new

  end

  def cow

  end

  def post_mailing
    @tester = Tester.new(tester_params)
    @tester.tester_email = @tester.tester_email.downcase
    if @tester.save
      redirect_to action: 'mailing_success'
    else
      render action: 'mailing'
    end
  end

  def login
    if !session[:current_user_id].nil? && session[:current_user_id] == 1
      redirect_to action: "control_panel"
    end
    @user = User.new
  end

  def post_login
    @user = User.new(user_login_params)
    @user.user_email = @user.user_email.downcase

    if(params[:user].nil? || params[:user][:user_email].nil? || params[:user][:user_password].nil?)
      flash[:login_msg] = "Username and/or password is incorrect."
      render :login
      return
    end

    @user = User.new
    @user.user_email = params[:user][:user_email].downcase
    @loggedInUser = User.find_by user_email: params[:user][:user_email].downcase
    if !@loggedInUser.nil? && @loggedInUser.password_valid?(params[:user][:user_password])
      flash[:login_msg] = nil
      session[:current_user_id] = @loggedInUser.id
      session[:current_user_email] = @loggedInUser.user_email
      redirect_to action: "control_panel"
      return
    end
    flash[:login_msg] = "Username and/or password is incorrect."
    render :login
  end

  def control_panel
    @allTesters = Tester.all
  end

  def logout
    reset_session
    redirect_to action: 'login'
  end

	private
  def tester_params
	  return params.require(:tester).permit(:tester_first_name, 
		  :tester_last_name,
		  :tester_email, 
		  :tester_organization, 
		  :tester_role
    )
  end

  def user_login_params
    return params.require(:user).permit(:user_email, :user_password)
  end
end
