**This version of Tremulous supports VOIP there are 2 different versions in at the moment**

**1. mumble support (http://mumble.sourceforge.net/)**: This allows mumble to display others ingame position. to use this feature start mumble then set the cvar cl\_usemumble to 1.

**2. Tremded VOIP Support**: Tremded gained VOIP support in [revision 1099](https://code.google.com/p/fsm-trem/source/detail?r=1099)
  * **quick start guide:**
    * _run our tremded and tremulous binaries or any client/server thats based on [revision 1099](https://code.google.com/p/fsm-trem/source/detail?r=1099)+_
    * _make sure /rate is 25000 or your connection settings are set to broadband or above._

  * **Tremded only info**
    * _set sv\_voip to 1._

  * **Tremulous client info**
    * _set cvar /snd\_useopenal to 1._
    * _bind "+voiprecord" to a key by doing /bind q +voiprecord or set the  cvar /cl\_voipsend 1 for automatic sending of chat._
    * _press the key you bound in the step above (in this example it was q) and talk._

**How is the default devices set.**
> in linux you need to write a _~/.openalrc_ file, here is a sample file replace "capture device" and "playback device" with the
> devices you want to use. (for example playback device might be set to
> "front" or "default")
```
		(define devices '(alsa))
		(define alsa-out-device "playback device")
		(define alsa-in-device "capture device")
		(define speaker-num 2)
```


---


**CVAR list from ioquake3 documentation and their functions:**

**sv\_voip:** set to "1" (the default) to enable server-side VoIP support. Set to
> "0" to disable. Without this, all VoIP packets are refused by the
> server, which means no one gets to use in-game VoIP.

**voip:** set to "1" (the default) to enable client-side VoIP support. Set to "0"
> to disable. Without this, you will neither be able to transmit voice nor
> hear other people.

**s\_alCapture:** set to "1" (the default) to have the audio layer open an OpenAL
> capture device. Without this set on sound startup, you'll never
> get bits from the microphone. This means you won't transmit, but
> you can still hear other people.

**cl\_voipSendTarget:** a string: "all" to broadcast to everyone, "none" to send
> to no one, "attacker" to send to the last person that hit
> you, "crosshair" to send to the people currently in your
> crosshair, or a comma-separated list of client numbers, like
> "0,7,2,23" ... an empty string is treated like "all". This
> is reset to "all" when connecting to a new server.
> Presumably mods will manage this cvar, not people, but
> keybind could be useful for the general cases. To send to
> just your team, or the opposing team, or a buddy list, you
> have to set a list of numbers.

**cl\_voipUseVAD:** set to "1" to automatically send audio when the game thinks you
> are talking, "0" (the default) to require the user to manually
> start transmitting, presumably with a keybind.

**cl\_voipVADThreshold:** only used if cl\_voipUseVAD is "1" ... a value between
> 0.0 and 1.0 that signifies the volume of recorded audio
> that the game considers to be speech. You can use this
> to trim out breathing or perhaps the sound of your
> fingers tapping the keyboard and only transmit audio
> louder than that. You will have to experiment to find the
> value that works best for your hardware and play style.
> The default is "0.25", with "0.0" being silence and "1.0"
> being pretty-darn-loud.

**cl\_voipSend:** when set to "1", the game will capture audio from the microphone
> and transmit it, when "0", the game will not. The game can
> optimize for the "0" case (perhaps turning off audio recording).
> Lots of things set this on and off, including cl\_voipUseVAD, so
> you probably should not touch this directly without knowing what
> you're doing, but perhaps mods can make use of it.

**cl\_voipGainDuringCapture:** This is the volume ("gain") of audio coming out of
> your speakers while you are recording sound for
> transmission. This is a value between 0.0 and 1.0,
> zero being silence and one being no reduction in
> volume. This prevents audio feedback and echo and
> such, but if you're listening in headphones that
> your mic won't pick up, you don't need to turn down
> the gain. Default is 0.2 (20% of normal volume). You
> ABSOLUTELY want to make your speakers quiet when you
> record, if the microphone might pick it up!

**cl\_voipShowMeter:** Set to "1" (the default) to show a volume meter as you are
> recording from the microphone, so you can see how well the
> game can "hear" you. Set to "0" to disable the display of
> the meter.

**cl\_voipCaptureMult:** Multiply recorded audio by this value after denoising.
> Defaults to 2.0 to _double_ the volume of your voice.
> This is to make you more audible if denoising eats away
> too much data. Set this to 1.0 to get no change, less to
> be quieter.

**Console commands:**

**voip ignore**

&lt;clientnum&gt;

**> Turn off incoming voice from player number**

&lt;clientnum&gt;

. This will refuse to
> > play any incoming audio from that player, and instruct the server to stop
> > sending it, to save bandwidth. Use unignore to reenable. This is reset to
> > unignored when (re)connecting to a server.

**voip gain unignore**

&lt;clientnum&gt;

**> Turn on incoming voice from player number**

&lt;clientnum&gt;

. This will start
> > playing audio from this player again if you've previously done a "voip
> > ignore", and instruct the server to start sending her voice packets to
> > you again.

**voip gain muteall**

> Turn off all incoming voice. This will refuse to play any incoming audio,
> > and instruct the server to stop sending it, to save bandwidth. Use
> > unmuteall to reenable. This is reset to unmuted when (re)connecting to
> > a server.

**voip gain unmuteall**

> Turn on incoming voice. This will start playing audio again if you've
> > previously done a "voip muteall", and instruct the server to start
> > sending voice packets to you again.

**voip gain**

&lt;clientnum&gt;

 

&lt;gain&gt;

**> Sets the volume ("gain") for player number**

&lt;clientnum&gt;

 to 

&lt;gain&gt;

 ...
> > A gain of 0.0 is silence, and 2.0 doubles the volume. Use this if someone
> > is too quiet or too loud.

**Actions:**

**+voiprecord:** The action you should bind to a key to record. This basically

> toggles cl\_voipSend on and off. You don't need this if you're
> using cl\_voipUseVAD, since that'll just record all the time and
> decide what parts of the recording are worth sending.