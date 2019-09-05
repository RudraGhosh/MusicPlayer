import os
import threading
import time
import tkinter.messagebox
from tkinter import *
from tkinter import filedialog

from tkinter import ttk
from tkinter.ttk import *
from ttkthemes import themed_tk as tk

from mutagen.mp3 import MP3
from mutagen.id3 import ID3
from mutagen.easyid3 import EasyID3
from mutagen import File
from pygame import mixer
from io import BytesIO
from PIL import Image, ImageTk
import sqlite3
from PyLyrics import *
from string import digits

root = tk.ThemedTk()
root.get_themes()
root.set_theme("radiance")
root.configure(background='cyan')
root.state('zoomed')

'''statusbar = ttk.Label(root, text="Welcome to PlayMusic", relief=SUNKEN, anchor=W, font='Times 10 italic')
statusbar.pack(side=BOTTOM, fill=X)'''

menubar = Menu(root)
root.config(menu=menubar)

subMenu = Menu(menubar, tearoff=0)

playlist = []
conn = sqlite3.connect('path.db')
c = conn.cursor()
c.execute('CREATE TABLE IF NOT EXISTS paths(song TEXT)')
conn2=sqlite3.connect('pos.db')
c2=conn2.cursor()
c2.execute('CREATE TABLE IF NOT EXISTS p(id INTEGER)')


# playlist - contains the full path + filename
# playlistbox - contains just the filename
# Fullpath + filename is required to play the music inside play_music load function

def browse_file():
    global filename_path
    filename_path = filedialog.askopenfilenames(defaultextension='.mp3',
                                                filetypes=[('MP3 Files', '.mp3'), ],
                                                title="Select .mp3 files",
                                                multiple=True, )
    for i in filename_path:
        if i not in playlist:
            global sid
            try:
                sid += 1
            except:
                pass
            data_entry(i)
            add_to_playlist(i)
    c.execute('SELECT DISTINCT song FROM paths')
    # mixer.music.queue(filename_path)


def data_entry(fname):
    c.execute("INSERT INTO paths (song) VALUES(?)", (fname,))
    conn.commit()


def add_to_playlist(fname):
    filename = os.path.basename(fname)
    index = 0
    playlistbox.insert(index, filename)
    playlist.insert(index, fname)
    index += 1


'''menubar.add_cascade(label="File", menu=subMenu)
subMenu.add_command(label="Open", command=browse_file)
subMenu.add_command(label="Exit", command=root.destroy)'''


def about_us():
    tkinter.messagebox.showinfo('About PlayMusic', 'This is a music player build using Python Tkinter')


subMenu = Menu(menubar, tearoff=0)
menubar.add_cascade(label="Help", menu=subMenu)
subMenu.add_command(label="About Us", command=about_us)
subMenu.add_command(label="Exit", command=root.destroy)

mixer.init()  # initializing the mixer

root.title("PlayMusic")
root.iconbitmap(r'mp.ico')

# Root Window - StatusBar, LeftFrame, RightFrame
# LeftFrame - The listbox (playlist)
# RightFrame - TopFrame,MiddleFrame and the BottomFrame
leftframe = tkinter.Frame(root, background='cyan')
leftframe.pack(side=LEFT, fill=BOTH)

plab = ttk.Label(leftframe, text='PLAYLIST', background='cyan', foreground='black', font='Times 20 bold')
plab.pack(side=TOP)
plbf=ttk.Frame(leftframe)
plbf.pack(side=TOP)
scb = tkinter.Scrollbar(plbf, orient='vertical')
playlistbox = tkinter.Listbox(plbf, width=52, height=33, yscrollcommand=scb.set, bg='cyan')
scb.config(command=playlistbox.yview)
playlistbox.pack(side=LEFT)
scb.pack(side=LEFT, fill=BOTH, expand=True)

def del_song():
    global sid
    selected_song = playlistbox.curselection()
    selected_song = int(selected_song[0])
    try:
        if (sid > selected_song):
            sid -= 1
    except:
        pass
    playlistbox.delete(selected_song, selected_song)
    t = playlist[selected_song]
    c.execute('DELETE FROM paths WHERE song=?', (t,))
    conn.commit()
    del playlist[selected_song]

abf=tkinter.Frame(leftframe,background='cyan')
abf.pack(side=BOTTOM,fill=BOTH,pady=10)
addBtn = ttk.Button(abf, text="+ Add", command=browse_file)
addBtn.pack(side=LEFT)
delBtn = ttk.Button(abf, text="- Del", command=del_song)
delBtn.pack(side=RIGHT)


clframe=ttk.Frame(root)
clframe.pack(fill=BOTH)

canvas = Canvas(clframe, width=400, height=400)
canvas.pack(side=RIGHT)
img = PhotoImage(file=r'albumarts/i.png')
image_on_canvas = canvas.create_image(200, 200, image=img)

canvas2=Canvas(clframe,width=500, height=400,background='cyan')
canvas2.pack(side=LEFT)
text_on_canvas2=canvas2.create_text(250,200,text='Lyrics',font='Times 16 roman')
vbar=ttk.Scrollbar(clframe,orient=VERTICAL)
vbar.config(command=canvas2.yview)
vbar.pack(side=RIGHT,fill=BOTH,expand=True)
canvas2.config(yscrollcommand=vbar.set)
root.update()
canvas2.config(scrollregion=canvas2.bbox("all"))

c.execute('SELECT DISTINCT song FROM paths')
data = c.fetchall()
for i in data:
    i = i[0]
    add_to_playlist(str(i))
try:
    c2.execute('SELECT id FROM p')
    s=c2.fetchall()
    s=s[0]
    s=int(s[0])
    playlistbox.selection_set(s,s)
    playlistbox.see(s)
except:
    pass

def show_details(play_song):
    # file_data = os.path.splitext(play_song)
    global tag
    try:
        audio = MP3(play_song)
        tag = ID3(play_song)
        total_length = audio.info.length

        # div - total_length/60, mod - total_length % 60
        mins, secs = divmod(total_length, 60)
        mins = int(mins)
        secs = int(secs)
        timeformat = '{:02d}:{:02d}'.format(mins, secs)
        lengthlabel['text'] = "Total Length" + ' - ' + timeformat
        try:
            tlab['text'] = 'Currently Playing' + ' - ' + tag['TIT2'].text[0]
            s=tag['TIT2'].text[0]
            s=s[0]
        except:
            tlab['text'] = 'Currently Playing' + ' - ' + os.path.basename(play_song)
        try:
            album['text'] = 'Album' + ' - ' + tag['TALB'].text[0]
        except:
            album['text'] = 'Album' + ' - ' + 'Unknown'
        try:
            artist['text'] = 'Artist' + ' - ' + tag['TPE1'].text[0]
            tem=threading.Thread(target=lyrics,args=(play_song,))
            tem.start()
        except:
            artist['text'] = 'Artist' + ' - ' + 'Unknown'
        try:
            music['text'] = 'Music' + ' - ' + tag['TCOM'].text[0]
        except:
            music['text'] = 'Music' + ' - ' + 'Unknown'
        try:
            dt = tag["APIC:"].data
            output = BytesIO(dt)
            image = Image.open(output)
            image2 = image.resize((400, 400), Image.ANTIALIAS)
            image2.save('albumarts\\i2.png', 'png')
            img['file'] = r'albumarts\\i2.png'
        except:
            try:
                dt = tag["APIC:"].data
                output = BytesIO(dt)
                image = Image.open(output)
                image2 = image.resize((400, 400), Image.ANTIALIAS)
                image2.save('albumarts\\i2.ppm', 'ppm')
                img['file'] = r'albumarts\\i2.ppm'
            except:
                img['file'] = r'albumarts\\i.png'
        t1 = threading.Thread(target=start_count, args=(total_length,))
        t1.start()
    except:
        tlab['text'] = 'Currently Playing' + ' - ' + os.path.basename(play_song)
        lengthlabel['text'] = "Total Length" + ' - ' + '--:--'
        currenttimelabel['text'] = "Current Time" + ' - ' + '--:--'

def lyrics(play_song):
    etag=EasyID3(play_song)
    tit=etag['title'][0]
    art=etag['artist'][0]
    rd=str.maketrans('','',digits)
    tit=tit.translate(rd)
    m=0
    for i in art:
        if(i=='&'):
            art=art.split('&')
            m=1
            break
        elif(i==','):
            art=art.split(',')
            m=1
            break
    if(m==1):
        for i in range(len(art)):
            sch=0
            for j in art[i]:
                if(j=='['or j=='-' or j=='(' or j=='{'):
                    break
                sch+=1
            art[i]=art[i][:sch]
            art[i]=art[i].lstrip()
            art[i]=art[i].rstrip()
    else:
        sch=0
        for j in art:
            if(j=='['or j=='-' or j=='(' or j=='{'):
                break
            sch+=1
        art=art[:sch]
        art=art.lstrip()
        art=art.rstrip()
    st=''
    f=0
    for i in tit:
        if(f==0 and (i==' ' or i.isalpha())):
            st=st+i
        if(i=='[' or i=='{' or i=='('or i=='-'):
            f=1
        elif(i==']' or i=='}'or i==')'):
            f=0
    tit=st
    tit=tit.lstrip()
    tit=tit.rstrip()
    if(m==1):
        for i in art:
            try:
                canvas2.itemconfig(text_on_canvas2,text='Lyrics Loading')
                d=PyLyrics.getLyrics(i,tit)
                canvas2.itemconfig(text_on_canvas2,text=d)
                root.update()
                canvas2.config(scrollregion=canvas2.bbox("all"))
                break
            except:
                canvas2.itemconfig(text_on_canvas2,text='No Lyrics Found For This Track!!')
                pass
    else:
        try:
            canvas2.itemconfig(text_on_canvas2,text='Lyrics Loading')
            d=PyLyrics.getLyrics(art,tit)
            canvas2.itemconfig(text_on_canvas2,text=d)
            root.update()
            canvas2.config(scrollregion=canvas2.bbox("all"))
        except:
            canvas2.itemconfig(text_on_canvas2,text='No Lyrics Found For This Track!!')
            pass

def start_count(t):
    global paused
    # mixer.music.get_busy(): - Returns FALSE when we press the stop button (music stop playing)
    # Continue - Ignores all of the statements below it. We check if music is paused or not.
    current_time = 0
    while current_time <= t and mixer.music.get_busy():
        if paused:
            continue
        else:
            mins, secs = divmod(current_time, 60)
            mins = round(mins)
            secs = round(secs)
            timeformat = '{:02d}:{:02d}'.format(mins, secs)
            currenttimelabel['text'] = "Current Time" + ' - ' + timeformat
            time.sleep(1)
            current_time += 1
            if (current_time >= t - 1 or mixer.music.get_busy == 0):
                stop_music()
                play_next()
                break


global sid


def play_music():
    global paused

    if paused:
        mixer.music.unpause()
        #statusbar['text'] = "Music Resumed"
        paused = FALSE
        playPhoto['file']='pause.png'
        playBtn['command']=pause_music
    else:
        try:
            #global temp
            global sid
            stop_music()
            time.sleep(1)
            try:
                selected_song = playlistbox.curselection()
                selected_song = int(selected_song[0])
            except:
                playlistbox.selection_set(0, 0)
                selected_song = 0
            '''try:
                if (temp == selected_song):
                    selected_song = sid
                else:
                    temp = selected_song
            except:
                temp = selected_song'''
            sid = selected_song
            play_it = playlist[selected_song]
            playlistbox.see(selected_song)
            try:
                mixer.music.load(play_it)
                mixer.music.play()
                #statusbar['text'] = "Playing music" + ' - ' + os.path.basename(play_it)
                show_details(play_it)
                playPhoto['file']='pause.png'
                playBtn['command']=pause_music
            except:
                tkinter.messagebox.showerror('File not found', 'File missing or removed or corrupted')
                playlistbox.delete(selected_song, selected_song)
                t = playlist[selected_song]
                c.execute('DELETE FROM paths WHERE song=?', (t,))
                conn.commit()
                del playlist[selected_song]
                play_music()
        except:
            tkinter.messagebox.showerror('File not found', 'PlayMusic could not find any file. Please check again.')


def play_prev():
    global sid
    global temp,paused
    try:
        if (sid != 0):
            sid -= 1
            playlistbox.selection_clear(sid + 1, sid + 1)
        else:
            playlistbox.selection_clear(sid, sid)
            sid = len(playlist) - 1
        stop_music()
        time.sleep(1)
        playlistbox.selection_set(sid, sid)
        playlistbox.see(sid)
        temp = sid
        play_it = playlist[sid]
        mixer.music.load(play_it)
        mixer.music.play()
        #statusbar['text'] = "Playing music" + ' - ' + os.path.basename(play_it)
        show_details(play_it)
        playPhoto['file']='pause.png'
        playBtn['command']=pause_music
        paused=FALSE
    except:
        try:
            s=playlistbox.curselection()
            s=int(s[0])
            sid=s
            play_prev()
        except:
            tkinter.messagebox.showerror('File not found', 'PlayMusic could not find any file. Please check again.')


def play_next():
    global sid
    global temp,paused
    try:
        if (sid != len(playlist) - 1):
            sid += 1
            playlistbox.selection_clear(sid - 1, sid - 1)
        else:
            playlistbox.selection_clear(sid, sid)
            sid = 0
        stop_music()
        time.sleep(1)
        playlistbox.selection_set(sid, sid)
        playlistbox.see(sid)
        temp = sid
        play_it = playlist[sid]
        mixer.music.load(play_it)
        mixer.music.play()
        #statusbar['text'] = "Playing music" + ' - ' + os.path.basename(play_it)
        show_details(play_it)
        playPhoto['file']='pause.png'
        playBtn['command']=pause_music
        paused=FALSE
    except:
        try:
            s=playlistbox.curselection()
            s=int(s[0])
            sid=s
            play_next()
        except:
            tkinter.messagebox.showerror('File not found', 'PlayMusic could not find any file. Please check again.')


def stop_music():
    mixer.music.stop()
    #statusbar['text'] = "Music Stopped"


paused = FALSE


def pause_music():
    global paused
    paused = TRUE
    mixer.music.pause()
    #statusbar['text'] = "Music Paused"
    playPhoto['file']='plb.png'
    playBtn['command']=play_music


def rewind_music():
    global sid,paused
    try:
        stop_music()
        time.sleep(1)
        play_it = playlist[sid]
        mixer.music.load(play_it)
        mixer.music.play()
        #statusbar['text'] = "Music Rewinded"
        show_details(play_it)
        playPhoto['file']='pause.png'
        playBtn['command']=pause_music
        paused=FALSE
    except:
        tkinter.messagebox.showerror('File not found', 'PlayMusic could not find any file. Please check again.')


def set_vol(val):
    volume = float(val) / 100
    mixer.music.set_volume(volume)
    # set_volume of mixer takes value only from 0 to 1. Example - 0, 0.1,0.55,0.54.0.99,1


muted = FALSE


def mute_music():
    global muted
    if muted:  # Unmute the music
        mixer.music.set_volume(0.7)
        volumeBtn.configure(image=volumePhoto)
        scale.set(70)
        muted = FALSE
    else:  # mute the music
        mixer.music.set_volume(0)
        volumeBtn.configure(image=mutePhoto)
        scale.set(0)
        muted = TRUE

def get_curr():
    global sid,paused
    try:
        s=playlistbox.curselection()
        s=int(s[0])
        sid=s
        stop_music()
        time.sleep(1)
        play_it = playlist[sid]
        mixer.music.load(play_it)
        mixer.music.play()
        #statusbar['text'] = "Playing music" + ' - ' + os.path.basename(play_it)
        show_details(play_it)
        playPhoto['file']='pause.png'
        playBtn['command']=pause_music
        paused=FALSE
    except:
        tkinter.messagebox.showerror('File not found', 'PlayMusic could not find any file. Please check again.')

playlistbox.bind('<Double-1>',lambda x:get_curr())

rightframe = tkinter.Frame(root, background='cyan')
rightframe.pack(side=BOTTOM, fill=X)

nframe = tkinter.Frame(root, background='cyan')
nframe.pack(side=BOTTOM, fill=X)
tlab = ttk.Label(nframe, text='Currently Playing -  ', anchor=W, font='Times 16 roman', background='cyan')
tlab.pack(pady=10, fill=X)
artist = ttk.Label(nframe, text='Artist-  ', anchor=W, font='Times 16 roman', background='cyan')
artist.pack(pady=5, fill=X)
album = ttk.Label(nframe, text='Album-  ', anchor=W, font='Times 16 roman', background='cyan')
album.pack(pady=5, fill=X)
music = ttk.Label(nframe, text='Music-  ', anchor=W, font='Times 16 roman', background='cyan')
music.pack(pady=10, fill=X)

# Bottom Frame for volume, rewind, mute etc.

bottomframe = tkinter.Frame(rightframe,background='cyan')
bottomframe.pack(side=RIGHT, padx=15, pady=15)

rewindPhoto = PhotoImage(file='refresh.png')
rewindBtn = ttk.Button(bottomframe, image=rewindPhoto, command=rewind_music)
rewindBtn.pack(side=LEFT)

mutePhoto = PhotoImage(file='speaker (3).png')
volumePhoto = PhotoImage(file='speaker (5).png')
volumeBtn = ttk.Button(bottomframe, image=volumePhoto, command=mute_music)
volumeBtn.pack(side=LEFT,padx=20)

scale = ttk.Scale(bottomframe, from_=0, to=100, orient=HORIZONTAL, command=set_vol)
scale.set(70)  # implement the default value of scale when music player starts
mixer.music.set_volume(0.7)
scale.pack(side=RIGHT)

middleframe = tkinter.Frame(rightframe,background='cyan')
middleframe.pack(side=LEFT, padx=20)

prevPhoto = PhotoImage(file='re.png')
prevBtn = ttk.Button(middleframe, image=prevPhoto, command=play_prev)
prevBtn.pack(side=LEFT)

playPhoto = PhotoImage(file='plb.png')
playBtn = ttk.Button(middleframe, image=playPhoto, command=play_music)
playBtn.pack(side=LEFT,padx=20)

skipPhoto = PhotoImage(file='skip.png')
skipBtn = ttk.Button(middleframe, image=skipPhoto, command=play_next)
skipBtn.pack(side=RIGHT)

'''pausePhoto = PhotoImage(file='pause.png')
pauseBtn = ttk.Button(middleframe, image=pausePhoto, command=pause_music)
pauseBtn.pack(side=RIGHT)'''

topframe = tkinter.Frame(rightframe)
topframe.pack(side=LEFT, padx=40)
lengthlabel = ttk.Label(topframe, text='Total Length : --:--', font='Times 16 roman', background='cyan',
                        foreground='black')
lengthlabel.pack(fill=X)

currenttimelabel = ttk.Label(topframe, text='Current Time : --:--', font='Times 16 roman', background='cyan',
                             foreground='black')
currenttimelabel.pack()


def on_closing():
    stop_music()
    try:
        s=playlistbox.curselection()
        s=int(s[0])
        c2.execute('DELETE FROM p')
        conn2.commit()
        c2.execute('INSERT INTO p (id) VALUES(?)',(s,))
        conn2.commit()
    except:
        pass
    root.destroy()


root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()
