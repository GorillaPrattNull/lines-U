    #!/bin/bash
    #
    #
    #  Usage is:
    #
    #    fut.sh <dir>
    #

    function recurse()
    {
      # 'cd' down into the named directory
      cd $1

      # Iterate through all of the files
      for file in * ; do

        # If the file is a directory, recurse
        if [ -d $file ] ; then

          recurse $file
        fi

        if [ -f "$file" ] ; then

#echo "test"
#echo $file
          longfile='ls -l --time-style=long-iso $file'
	  #ls -l --time-style=long-iso $file
          check='echo $longfile | grep $today'

 #         echo $longfile
#	  echo $check
#	  echo $longfile "|" $today
          if [ -n "$check" ] ; then

            echo $PWD/$file

          fi

        fi

      done

      if [ $1 != . ] ; then
        cd ..
     fi

   }


    function main()
    {
      today='date +%Y-%m-%d'
#echo `$today`
      checkdir=$1

      if [ -z $checkdir ] ; then
        checkdir=.
      fi

      recurse $checkdir
    }

    main $1

    exit
