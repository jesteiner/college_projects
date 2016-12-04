from django.contrib.auth.models import User # Gives us the base, generic User class. 
from django import forms

class UserForm*(forms.ModelForm): # Creates a new class called Userform that inherits from ModelForm in forms, which we imported from django. 
	
	password = forms.CharField(widget=forms.PasswordInput) # CharField() by itself would display plaintext, so (widget=forms.PasswordInput) displays asterisks in the password input field. 
	class Meta:
		model = User
		fields = ['username', 'email', 'password']

