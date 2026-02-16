pipeline {
  agent any

  environment {
    IMAGE_NAME = 'array_list_c'
    VER        = 'latest'
    IMAGE_TAG  = "${IMAGE_NAME}:${VER}"
  }

  stages {
    stage('Checkout') {
      steps {
        git branch: 'main', url: 'https://github.com/AmitNachum/Array_List_C.git'
      }
    }

    stage('Build') {
      steps {
        sh '''
          set -e
          echo "building docker image: $IMAGE_TAG"
          docker build -t "$IMAGE_TAG" .
        '''
      }
    }

    stage('Push to Docker') {
      steps {
        withCredentials([usernamePassword(
          credentialsId: 'array_list_C',
          usernameVariable: 'DOCKER_USER',
          passwordVariable: 'DOCKER_PASS'
        )]) {
          sh '''
            set -e
            echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin
            docker push amitnachum/"$IMAGE_TAG"
            docker logout
          '''
        }
      }
    }
  }

  post {
    always {
      echo '====== PIPELINE IS DONE ======'
    }
  }
}
