Here is a little F.A.Q. page to help you along with upgrading your client.

**Q**. When i use your client, it seems alot brighter, how do i fix it?

**A**. In the new clients, gamma was changed to be alot brighter than the old, to fix this try the following.

  * _Type /r\_gamma 1.5, or /r\_gamma 2, if that doesn't work, try the below line._
  * _Type /r\_overBrightBits 0, and see if that fixes it._

If neither of those help, please contact a project member.


---


**Q**. When I try to use your client on Mac OS X (10.2.x PPC) it says my platform is unsupported?

**A**. The use of the 10.2.8 SDK is broken in the latest Tremulous SVN. Until this is fixed, backwards compatibility is only supported on 10.3.x and above on both PPC and Intel Platforms.


---


**Q**. When i try to make a server in tremulous, my tremulous crashes!

**A**. This is due to a backporting problem, simply place http://tremfusion.net/releases/0.0.3/r1/misc/tremfusion-base.pk3 file in your base folder, and it should work again.


---


**Q**. When I try to run Tremulous, it says X.dll was not found!

**A**. Unzip and place the contents of the [Windows Dynamic Link Libraries (DLL)](http://fsm-trem.googlecode.com/files/dll-library.zip) package besides your tremulous executable. This includes an mp3, ogg, vorbis, curl, and Lakitu7 SDL libraries.


---


**Q**. When i try to compile from your SVN, I get random mp3/ogg errors.

**A**. Our SVN has MP3 and OGG support on by default, you will either need to do two things

_1_: You need to install the correct libraries to your compiling environment, as explained by the following...

(Linux) - You need to add libmad, libogg, and libvorbis from your distro's repos.

(Windows) - **Insert windows instructions here**

(Mac OSX) - Use the script to make a universal binary.  Universal versions of the necessary libraries have been added to svn, but they may or may not work when the client is started via a command-line.

_2_: Or you can disable MP3 and OGG support in the makefile, open the makefile, and scroll down till you see "USE\_CODEC\_MP3" and "USE\_CODEC\_VORBIS", and set both to 0 to disable support