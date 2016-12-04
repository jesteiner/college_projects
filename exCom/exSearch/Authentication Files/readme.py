
# Django authentication relies on 4 componenents that are installed by default.

# Here is the list of them. 

# The first two are in INSTALLED_APPS of settings.py when you startproject. 

# 1.  'django.contrib.auth'
# 2.  'django.contrib.contenttypes'

# The next two are in MIDDLEWARE 

# 3.   'django.contrib.sessions.middleware.SessionMiddleware'
# 4.   'django.contrib.auth.middleware.AuthenticationMiddleware'

# Again, they should be here by default, but in case something changed and took them out, put them back into settings.py in their respective places, then
# run 'python manage.py migrate'. 

# For the interests of time, we will do generic authentication, instead of adding advanced features like password validation and throttling excessive log in attempts. 

# Perform the steps in part 9 of the tutorials with creating the super user before doing this. I don't quite have access to all the files in the database, so I will be writting code
# that should work, with placeholders, and then it will be up to you to configure the groups and permissions using the provided gui on the django website as you see fit. Probably just
# using common sense is sufficent for a barebones implementation.

# In some places, I will add placeholder, and will add comments to contextually specify what you should be replacing stuff for. 

# Add the forms.py file and merge the views.py file with your current views as appropriate, for imports and code that wasn't already there. 
# Place registration_form.html in the directory template, as we did in the django tutorials. 

# I didn't write a front end html code for the registration and login forms because I was tasked with desgigning the back end, which this should accomplish. Place the registration_html in the directory 
# template and inser the front end code, and it should work, provided everything else has been placed properly. 

# Important note: When done, you need to update the url patterns in the directory url file. 
# Maybe something like url(r'^register/$', views.UserFormView, name='register')
# register is just a placeholder name I suggested. 