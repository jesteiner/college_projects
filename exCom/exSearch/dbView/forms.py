from django import forms

from .models import Exercise

class PostForm(forms.ModelForm):

    class Meta:
        model = Exercise
        fields = ('activityType', 'difficultyrating', 'notes', 'address', 'zipcode',)
