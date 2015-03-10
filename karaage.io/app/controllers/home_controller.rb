class HomeController < ApplicationController
	def index

	end

  def about

  end

  def cow

  end

  def contact
    @tester = Tester.new

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
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    current_user = User.find_by_id session[:current_user_id]
    if current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    @timeNow = Time.now
    @timeNow = @timeNow.strftime("%Y-%m-%d")
    @allPosts = Post.all
    @post = Post.new
  end

  def post_post
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    current_user = User.find_by_id session[:current_user_id]
    if current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    @post = Post.new(post_params)
    @post.post_date = DateTime.strptime(@post.post_time, "%Y-%m-%d")
    @post.user = User.find_by_id session[:current_user_id]
    @post.post_content = ActionController::Base.helpers.sanitize(@post.post_content, tags: %w(h1 h2 h3 h4 h5 h6 hr ul ol li strong em b i p dd dl table tr td img), attributes: %w(class))

    if @post.save
      redirect_to action: "control_panel"
    else
      render action: "control_panel"
    end
  end

  def view_post
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    current_user = User.find_by_id session[:current_user_id]
    if current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: "control_panel"
    end

    @timeNow = @post.post_date.strftime("%Y-%m-%d")
  end

  def edit_post
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    current_user = User.find_by_id session[:current_user_id]
    if current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    edit_post = Post.new(post_params)
    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: "control_panel"
      return
    end

    @post.post_date = DateTime.strptime(edit_post.post_time, "%Y-%m-%d")
    @post.user = User.find_by_id session[:current_user_id]
    @post.post_content = ActionController::Base.helpers.sanitize(edit_post.post_content, tags: %w(h1 h2 h3 h4 h5 h6 hr ul ol li strong em b i p dd dl table th tr td img), attributes: %w(class))

    if @post.save
      redirect_to action: "control_panel"
    else
      render action: "control_panel"
    end
  end

  def delete_post
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    current_user = User.find_by_id session[:current_user_id]
    if current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: "control_panel"
      return
    end
    
    Post.destroy params[:id]

    redirect_to action: "control_panel"
  end

  def user_control_panel
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

  def post_params
    return params.require(:post).permit(:post_time, :post_title, :post_content, :post_is_published)
  end
end
