package com.example.demo.gof.c_behavioral.memento;

import java.util.ArrayList;
import java.util.List;

public class BookmarkInfo {
    List<Bookmark> bookmarks = new ArrayList<>();
    public void add(Bookmark bookmark){
        bookmarks.add(bookmark);
    }

    public Bookmark get(int idx){
        return bookmarks.get(idx);
    }
}
