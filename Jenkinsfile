pipeline {
  agent none
  stages {
    stage('Build') {
      agent {
        label 'windows'
      }
      steps {
        checkout scm
        dir('buildMSVC-x64') {
          // BUG Jenkins can't find cmake
          bat '"C:/Program Files/CMake/bin/cmake" .. -DCMAKE_PREFIX_PATH=C:/Qt/5.12.0/msvc2017_64 -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017 Win64"'
          bat '"C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/MSBuild/15.0/Bin/MSBuild.exe Properties="Configuration=Release"" Notefad.sln' 
          // Deletes the Jenkins Workspace
          deleteDir()
          
        }// buildMSVC-x64
        
      }//steps
    } //stage Build
  
  } //stages

}// pipeline