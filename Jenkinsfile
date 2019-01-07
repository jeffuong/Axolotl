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
          //BUG Jenkins can't find cmake
          bat 'C:/Program Files/CMake/bin/cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/5.12.0/msvc2017_64 -G "Visual Studio 15 2017 Win64"'
        }
      }
    }
  
  }



}