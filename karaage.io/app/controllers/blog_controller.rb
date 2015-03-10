class BlogController < ApplicationController
	def index
    @current_user = User.find_by_id session[:current_user_id]
    @allPosts = Post.where(post_is_published: 1).order("post_date DESC")
    @months = Post.all.group_by { |p| p.created_at.beginning_of_month }
	end

  def view
    @current_user = User.find_by_id session[:current_user_id]
    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: index
    end
  end
end
