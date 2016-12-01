from django.conf.urls import url, include
from django.views.generic import ListView, DetailView
from dbView.models import Exercise
from . import views

urlpatterns = [
 
                url(r'^main/', views.main),
		url(r'^new/', views.post_new, name='post_new'),
		url(r'^$', ListView.as_view(queryset=Exercise.objects.all(), template_name="dbView/results.html")),
                url(r'^(?P<pk>\d+)$', DetailView.as_view(model=Exercise, template_name="dbView/exDetail.html"), name='post_detail'),
		url(r'^search/(?P<zip_id>[0-9]+)/$', ListView.as_view(queryset=Exercise.objects.all().filter(zipcode="zip_id"), template_name="dbView/results.html")),
		]
