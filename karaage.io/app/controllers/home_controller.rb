class HomeController < ApplicationController
	def index
    @current_user = User.find_by_id session[:current_user_id]
	end

  def cow
    @current_user = User.find_by_id session[:current_user_id]
  end

  def contact
    @current_user = User.find_by_id session[:current_user_id]
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

    @current_user = User.find_by_id session[:current_user_id]
    if @current_user.user_email != session[:current_user_email]
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
      flash[:success] = "Post saved."
      redirect_to action: "control_panel"
    else
      @timeNow = Time.now
      @timeNow = @timeNow.strftime("%Y-%m-%d")
      @allPosts = Post.all
      render action: "control_panel"
    end
  end

  def view_post
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    @current_user = User.find_by_id session[:current_user_id]
    if @current_user.user_email != session[:current_user_email]
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
    @post.post_content = ActionController::Base.helpers.sanitize(edit_post.post_content, tags: %w(a br div h1 h2 h3 h4 h5 h6 hr ul ol li strong em b i p dd dl table th tr td img video source), attributes: %w(class src href controls type autoplay loop muted))
    @post.post_is_published = edit_post.post_is_published

    if @post.save
      flash[:success] = "Post edited."
      redirect_to action: "control_panel"
    else
      render action: "edit_post"
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
    flash[:success] = "Post deleted."
    redirect_to action: "control_panel"
  end

  def user_control_panel
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    @current_user = User.find_by_id session[:current_user_id]
    if @current_user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    @allTesters = Tester.all
  end

  def user_admin
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    @user = User.find_by_id session[:current_user_id]
    @current_user = @user
    if @user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end
    @passUser = User.new
  end

  def edit_user
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    @user = User.find_by_id session[:current_user_id]
    if @user.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    edit = User.new(user_edit_params)
    if @user.password_valid?(edit.user_password)
      @user.user_first_name = edit.user_first_name
      @user.user_last_name = edit.user_last_name
      @user.user_bio = edit.user_bio
      @user.user_organization = edit.user_organization
      @user.user_password = edit.user_password
      if @user.save
        flash[:success] = "User information changed."
        redirect_to action: "user_admin"
        return
      else
        @passUser = User.new
        render action: "user_admin"
        return
      end
    end
    flash[:error] = "Password is incorrect."
    render action: "user_admin"
  end

  def new_user
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end

    @current_user = User.find_by_id session[:current_user_id]
    if @current_user.user_email != session[:current_user_email] || @current_user.user_privileges != 1
      reset_session
      redirect_to action: "index"
      return
    end

    @newUser = User.new(user_new_params)
    @newUser.user_privileges = 2
    @newUser.user_email = @newUser.user_email.downcase
    @newUser.password = @newUser.user_password
    if @newUser.save
      flash[:success] = "User added."
      redirect_to action: "user_admin"
      return
    else
      @user = User.new
      @passUser = User.new
      render action: "user_admin"
      return
    end
  end

  def change_password
    if not session[:current_user_id] or not session[:current_user_email]
      redirect_to action: "index"
      return
    end
    @user = User.new
    @passUser = User.find_by_id session[:current_user_id]
    if @passUser.user_email != session[:current_user_email]
      reset_session
      redirect_to action: "index"
      return
    end

    old_password = params[:user][:user_password]
    if @passUser.password_valid?(old_password)
      @passUser.password = params[:user][:user_new_password]
      @passUser.user_password = params[:user][:user_new_password]
      if @passUser.save
        flash[:success] = "Password changed."
        @passUser = User.new
        redirect_to action: "user_admin"
      else
        render action: "user_admin"
      end
      return
    end
    flash[:error] = "Password is incorrect."
    render action: "user_admin"
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

  def user_edit_params
    return params.require(:user).permit(:user_first_name, :user_last_name, :user_bio, :user_organization, :user_password, :user_profile_url)
  end

  def user_new_params
    return params.require(:user).permit(:user_first_name, :user_last_name, :user_email, :user_bio, :user_organization, :user_password, :user_profile_url)
  end

  def post_params
    return params.require(:post).permit(:post_time, :post_title, :post_content, :post_is_published)
  end
end
