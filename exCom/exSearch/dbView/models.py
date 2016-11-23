from __future__ import unicode_literals
from django.db import models

class Exercise(models.Model):
	zipcode = models.CharField(max_length=5, null=True)
	address = models.CharField(max_length=200, null=True)
	notes = models.TextField(null=True)
	activityType = models.CharField(max_length=25, null=True) 
	difficultyrating = models.CharField(max_length=1, null=True)

	def __unicode__(self):
		return self.zipcode

	def publish(self):
		self.save()
