# olicrypt
<p>Simple stdin to stdout encryption tool<p>
<br/>
<p>Created for self-learning and having some encryption code for other potential tools</p>
<pre>olicrypt
  by Olivier Van Rompuy

  Syntax : olicrypt [-d] [-r rounds] keystring
   -d   Decrypt
   -r   #Rounds</pre>
<br/>
<p>Example use : encrypt and decrypt a file</p>
<pre>$ olicrypt -r 8 mysecretkey &lt;testfile &gt;testfile.enc
$ olicrypt -d -r 8 mysecretkey <testfile.enc >testfile.dec</pre>