.. Copyright (c) 2016, Ruslan Baratov
.. All rights reserved.

rtfd-css
========

Custom ``*.css`` used in various projects. Usage:

#. Add `this`_ repository as a submodule
#. Modify ``conf.py`` (see `patch`_):
    * ignore documentation files from ``rtfd-css`` directory
    * add ``rtfd-css/docs/rtfd-css`` directory to the static paths
    * load CSS by ``add_stylesheet``

.. toctree::
   :maxdepth: 2

   /examples
   /bug

Used by:

* https://docs.hunter.sh
* http://cgold.rtfd.io

.. _this: https://github.com/ruslo/rtfd-css
.. _patch: https://github.com/ruslo/CGold/commit/7c45924567fe3fd53e8a900935fdcaf35d62febf
