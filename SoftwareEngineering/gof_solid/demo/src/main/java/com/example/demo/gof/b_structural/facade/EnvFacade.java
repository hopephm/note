package com.example.demo.gof.b_structural.facade;

public class EnvFacade {
    OSSetter osSetter;
    VersionSetter versionSetter;

    public void setOsSetter(OSSetter osSetter){
        this.osSetter = osSetter;
    }

    public void setVersionSetter(VersionSetter versionSetter){
        this.versionSetter = versionSetter;
    }

    public void init(){
        this.setOsSetter(new OSSetter());
        this.setVersionSetter(new VersionSetter());
    }

    public void setEnv(){
        osSetter.setOS();
        versionSetter.setVersion();
    }
}
