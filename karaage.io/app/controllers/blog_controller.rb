class BlogController < ApplicationController
	def index
    @allPosts = Post.where post_is_published: 1
	end

  def view
    @post = Post.find_by_id params[:id]
    if not @post
      redirect_to action: index
    end
  end
end
