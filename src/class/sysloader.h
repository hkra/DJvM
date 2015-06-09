#pragma once

namespace System
{
    /*
     * System class loader
     *
     * Loads (bootstraps) classes required specified for execution or required by other
     * classes. Class loader only loads classe files. Their layout in memeory during runtime
     * is responsibility of the execution engine, which requests the class (probably a stupid
     * idea. I'll consider changing this as the project structure gets more solidified). 
     *
     *  Java class file specification can be found in chapter 5 of the JVM specification.
     *
     */
    class ClassLoader
    {
    public:
        
    private:
        
    };
}