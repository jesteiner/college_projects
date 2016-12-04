from django.shortcuts import render, redirect, render_to_response
from django.http import Http404, HttpResponse, HttpResponseRedirect
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

def main(request):
	return render(request, 'dbView/main.html')

def home(request):
	return render(request, 'dbView/homepage.html')

def activity(request):
	return render(request, 'dbView/activitypage.html')

def results(request):
	return render(request, 'dbView/searchresults.html')



#def search(request):
#
 #   if request.POST:
#	uInput = request.POST['term']
#	return HttpResponseRedirect("/")
 #   else:
#	return render_to_response('search.html')
