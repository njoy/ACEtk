# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'ACEtk'
copyright = '2026, Wim Haeck'
author = 'Wim Haeck'
release = '0.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

# point to the folder containing the njoy. python bindings .so file
import os
import sys
sys.path.insert( 0, '../' )

extensions = [
    'sphinx.ext.autodoc',
    'numpydoc'
    ]

templates_path = ['_templates']
exclude_patterns = []



####################
# numpydoc settings
#   see https://numpydoc.readthedocs.io/en/latest/install.html
####################

# this makes the types in the doc string parameters
# section clickable
numpydoc_xref_param_type = True

# this is a hacky way to avoid the "python:float" type in
# the parameter list
numpydoc_xref_aliases = {
    'float': 'float',
    'list': 'list',
    'bool': 'bool',
    'int': 'int',
    'str': 'str',
    'None': 'None'
}

# this is how to get numpydoc to not parse everything in
# the parameter types as a type (like default, of)
numpydoc_xref_ignore = {
    'type',
    'list',
    'of',
    'default',
    'true',
    'false',
    'none',
    }

# make a new toctree entry for each class
numpydoc_class_members_toctree = False

# keep these false - otherwise the attributes and methods
# are repeated twice on the page because autosummary is
# being used
numpydoc_show_class_members = False
numpydoc_show_inherited_class_members = False

####################
# autodoc settings
####################

autodoc_default_options = {
    'exclude_members': '__init__',
}

# in order to have the init signature come after the class
# name, these both need to be set this way:
autodoc_docstring_signature = True
autoclass_content = 'both' #  needs be 'both' or 'init'
# best bet is to use "both" and put nothing in the init doc string



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output


html_theme = 'pydata_sphinx_theme'
# html_theme = 'haiku'
html_static_path = ['_static']

# for pydata theme
html_theme_options = {
    "secondary_sidebar_items": [] # remove right column
}
