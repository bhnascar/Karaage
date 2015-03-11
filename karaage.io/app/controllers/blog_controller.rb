class BlogController < ApplicationController
	def index
    offset = params[:id].to_f
    if not offset or offset < 0
      offset = 0
    end
    @current_user = User.find_by_id session[:current_user_id]
    @allPosts = Post.where(post_is_published: 1).order("post_date DESC").limit(5).offset(offset * 5)
    @months = Post.all.group_by { |p| p.post_date.beginning_of_month }
    @postCount = Post.where(post_is_published: 1).count
	end

  def view
    @current_user = User.find_by_id session[:current_user_id]
    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: index
    end
  end
end
