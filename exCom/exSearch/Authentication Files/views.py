from django.shortcuts import render, redirect # Redirect will redirect them to the homepage after they log in. 
from django.contrib.auth import authenticate, login # The needed stuff for authentication. Also helps to provide a session id so they don't need to log in on every page. 

from django.views.generic import View
from .forms import UserForm #Here is us importing the forms.py file we are creating. 

# Inherits from the UserForm class in forms.py

class UserFormView(View):
	form_class = UserForm
	template_name = 'placeholder/registration_form.html' # Put the name of the directory in placeholder.

	# Blank form

	def get(self, request):
		form = self.form_class(None)
		return render(request, self.template_name, {'form': form})

	# Process form data

	def post(self, request): # When the user hits submit, the data is stored in POST due to built in django functionality. Processed here. 
		form = self.form_class(request.POST)

		if form.is_valid():

			user = form.save(commit=False) # Creates a user object from the form, but doesn't save it to the database yet. 

			# Need to clean the data first. Cleaning means the data is formatted properly in a normalized and unified way. 

			username = form.cleaned_data['username']
			password = form.cleaned_data['password']
			user.set_password(password) # Need to use a function to set the password becuase it is hashed by algorithms, not normal text. 
			user.save() # Saves them to the database.

			user = authenticate(username=username, password=password) # Takes the user name and password in the parameter and checks the database to see if they exist. 

			if user is not None:

				if user.is_active: # If they aren't banned by admin. 
					login(request, user) #logs user in. 
					return redirect('placeholder') # Put the url you want to redirect them to. It might be placeholder_directory_name:index

		return render(request, self.template_name, {'form': form}) # Re-render the form if credentials are invalid. 