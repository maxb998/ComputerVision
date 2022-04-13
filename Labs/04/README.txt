One cmake file, one executable created for all tasks.

this is how I compiled the sources:
    from a terminal window in <PROJECT_MAIN_FOLDER> :

        cd build
        cmake ..
        make
    
    DONE

this is how the command I used to run the executable, if you want to try the "automatic" image fetching, which is based on default picture location inside /doc
you have to leave the folders arrangment exactly as it is ad run the executable by specifying full path to it,, for example:

    <PATH_TO_PROJECT_DIR>/build/src/lab04 <TASK_NUMBER>

OTHERWISE there is the easier to explain procedure
where you just execute the main file with a command like the one below

    <PATH_TO_EXEC>/lab04 <TASK_NUMBER> <PICTURE_PATH>


The report is inside the doc folder