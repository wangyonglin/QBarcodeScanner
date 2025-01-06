TEMPLATE = subdirs

 SUBDIRS = \
    examples/application \
    BarcodeScanner

 # where to find the sub projects - give the folders

 BarcodeScanner.subdir = BarcodeScanner
 application.subdir  = examples/application

 # what subproject depends on others
 application.depends = BarcodeScanner
