### SecretProviderClass
- AWS Secrets and Configuration Provider를 위한 쿠버네티스 커스텀 리소스
  - Secrets Store CSI Driver를 위한 커스텀 리소스
  - Pod가 마운트할 외부 시크릿 정보를 정의
  - 예시
```
apiVersion: secrets-store.csi.x-k8s.io/v1
kind: SecretProviderClass
metadata:
  name: aws-secrets
spec:
  provider: aws
  parameters:
    objects: |
      - objectName: "arn:aws:secretsmanager:us-east-2:777788889999:secret:MySecret-a1b2c3"
        jmesPath: 
            - path: username
              objectAlias: dbusername
            - path: password
              objectAlias: dbpassword

```


### Secrets Store CSI Driver
- CSI(Container Storage Interface) 드라이버 중 하나로, 쿠버네티스에서 외부 시크릿(Secrets)과 인증서를 Pod에 마운트할 수 있게 해주는 드라이버
  - 쿠버네티스 클러스터 내 서비스로 직접 설치 필요
- AWS Secrets Manager, Azure Key Vault, HashiCorp Vault 등 외부 비밀 관리 시스템과 통합 가능
- PV/PVC와 달리 볼륨처럼 마운트되지만 데이터가 외부 시크릿에서 직접 제공됨

레퍼런스
- aws: https://docs.aws.amazon.com/ko_kr/secretsmanager/latest/userguide/ascp-eks-installation.html
- csi-driver: https://github.com/aws/secrets-store-csi-driver-provider-aws