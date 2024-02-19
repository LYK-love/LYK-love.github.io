---
title: Downloading Tools
tags:
---





# Wget

# Curl

```sh
curl -O <file>
```



# gdown

[Source](https://stackoverflow.com/questions/25010369/wget-curl-large-file-from-google-drive)

To download Google Drive files via CLI, you can use [gdown](https://github.com/wkentaro/gdown). 

* Only works on open access files. ("Anyone who has a link can View")

Install it with the following command:

```
pip install gdown
```

After that, you can download any file from Google Drive by running one of these commands:

```
gdown https://drive.google.com/uc?id=<file_id>  # for files
gdown <file_id>                                 # alternative format
gdown --folder https://drive.google.com/drive/folders/<file_id>  # for folders
gdown --folder --id <file_id>                                   # this format works for folders too
```

Example: to download the readme file from [this directory](https://drive.google.com/drive/folders/0B7EVK8r0v71pWEZsZE9oNnFzTm8)

```
gdown https://drive.google.com/uc?id=0B7EVK8r0v71pOXBhSUdJWU1MYUk
```

The `file_id` should look something like `0Bz8a_Dbh9QhbNU3SGlFaDg`. You can find this ID by right-clicking on the file of interest, and selecting *Get link*. As of November 2021, this link will be of the form:

```
# Files
https://drive.google.com/file/d/<file_id>/view?usp=sharing
# Folders
https://drive.google.com/drive/folders/<file_id>
```

