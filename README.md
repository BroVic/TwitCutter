# TwitCutter

_**Pre-release version**: This project is still under active development._

TwitCutter helps to cut up a large body of text that exceeds [Twitter](https://twitter.com)'s character limit(s). It can be used from the command line or with a graphical user interface.

## How to Use
Binaries have not yet been released (except one of the 3rd party libraries) and source files should be built with `cl.exe` using current project settings.  
### From the command line
To start up the application, simply run this line
```
./twitcut
```  
The user will be prompted to provide the path to the file whose text is to be posted.

### From the GUI
Using the application menu, open the file and view the text in the window--the displayed text is editable. When satisfied, navigate to the `TwitCutter` menu and click on `Generate` to create the chain of tweets from the text. This is also displayed in the window in an editable format. Then click on `TwitCutter` > `Post` to send the data to the Twitter feed.

The application supports text transfers using the Windows Clipboard (i.e. *Cut-Copy-Paste*) - such text should be pasted directly into the main window before processing it into tweets.

## Credits
Access to Twitter's REST API is accomplished with [BroVic's fork](https://github.com/BroVic/twitcurl) of [swatkat](https://github.com/swatkat)'s C++ library, **twitcurl**.
