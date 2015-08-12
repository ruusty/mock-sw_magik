# mock sw_magic #

2015-08-12

<a name="TOC"></a>
# Table of Contents

- [Description](#Description)
- [Behaviour](#Behaviour)

<a name="Description"></a>
## Description [^](#TOC) ##

A mocking replacement the *Smallworld GIS* executable `sw_magik.exe`

Set via configuration of the environment variable `SMALLWORLD_GIS`

Example setting `SMALLWORLD_GIS` to

	SMALLWORLD_GIS                   D:\ProjectsV3\mock_sw_magic  

The sub-directory path is `bin\x86\sw_magik.exe` which expands to `D:\ProjectsV3\mock_sw_magic\bin\x86\sw_magik.exe` 

This is configured in the batch job `*.tt` configuration file.

<a name="Behaviour"></a>
## Behaviour [^](#TOC) ##

#### JobReportPath ####

Gets the `JobReportPath` filename from the environment variable.

~~~
 	 string JobName = getEnv("POSH_JobName");
	 string JobReportPath = getEnv("POSH_JobReportPath");
~~~


#### Stdin Redirection ####

Handles redirected stdin like `sw_magik.exe`.	Copies the redirected stdin to the file `JobReportPath`

#### Environment Variables ####

Outputs environment variables and values to `JobReportPath`.

Outputs environment variables and values to stdout.

#### Command line arguments ####

Outputs command line arguments to stdout.
