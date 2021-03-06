#ifndef GMAILOAUTH_H
#define GMAILOAUTH_H

#include "oauth-agents/interfaces/oauthagent.h"

#include <chrono>

class GmailOauth : public OAuthAgent {
 public:
  GmailOauth(const std::string& clientId,
             const std::string& clientSecret,
             const std::string& redirectUri);

  GmailOauth(const std::string& clientId,
             const std::string& clientSecret,
             const std::string& redirectUri,
             const std::string& refreshToken);

 public:
  virtual std::string getUserUrl() const override;
  virtual void loadAccessToken(const std::string& userCode) noexcept(
      false) override;
  virtual void refreshAccessToken() noexcept(false) override;
  virtual std::pair<std::string, std::string> getAuthParam() const override;
  virtual bool isExpired() const override;
  virtual std::string getRefreshToken() const override;

 private:
  std::string mClientId;
  std::string mClientSecret;
  std::string mRedirectUri;
  std::string mGrantType;

  std::string mAccessToken;
  std::string mRefreshToken;
  std::string mTokenType;

  std::chrono::system_clock::time_point mExpiresAt;
};

#endif  // GMAILOAUTH_H
