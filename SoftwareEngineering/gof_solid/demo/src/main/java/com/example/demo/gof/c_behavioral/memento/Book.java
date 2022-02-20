package com.example.demo.gof.c_behavioral.memento;

public class Book {
    private int currentPage;

    public Book(){
        this.currentPage = 0;
    }

    public int getCurrentPage(){
        return currentPage;
    }

    public void read(){
        currentPage += 10;
    }

    public Bookmark bookmarking(){
        return new Bookmark(this.currentPage);
    }

    public void openPage(Bookmark bookmark){
        this.currentPage = bookmark.getPage();
    }
}
