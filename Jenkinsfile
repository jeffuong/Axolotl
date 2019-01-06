pipeline {
  agent none
  stages {
    stage('Build') {
      agent {
        label 'windows'
      }
      steps {
        checkout scm
        mkdir Notefad/buildMSVC-x64
        cd Notefad/buildMSVC-x64
        cmake .. -G "Visual Studio 15 2017 Win64"
      }
    }
  
  }



}