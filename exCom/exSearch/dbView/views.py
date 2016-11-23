from django.shortcuts import render, redirect
from .models import Exercise
from .forms import PostForm

def post_new(request):
	if request.method == "POST":
        	form = PostForm(request.POST)
		if form.is_valid():
            		post = form.save(commit=False)
            		post.save()
            		return redirect('post_detail', pk=post.pk)
	
	else:
		form = PostForm()

	return render(request, 'dbView/post_edit.html', {'form': form})
