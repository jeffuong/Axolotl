pipeline {
  agent none
  stages {
    stage('Build') {
      agent {
        label 'windows'
      }
      steps {
        checkout scm
        bat 'powershell.exe mkdir foobar'
        //bat "mkdir Notefad/buildMSVC-x64"
        //bat Notefad/buildMSVC-x64
        //bat "cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/5.12.0/msvc2017_64 -G "Visual Studio 15 2017 Win64""
      }
    }
  
  }



}