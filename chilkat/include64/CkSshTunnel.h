// CkSshTunnel.h: interface for the CkSshTunnel class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkSshTunnel_H
#define _CkSshTunnel_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkClassWithCallbacks.h"

class CkTask;
class CkSshKey;
class CkSsh;
class CkBaseProgress;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkSshTunnel
class CK_VISIBLE_PUBLIC CkSshTunnel  : public CkClassWithCallbacks
{
    private:

	// Don't allow assignment or copying these objects.
	CkSshTunnel(const CkSshTunnel &);
	CkSshTunnel &operator=(const CkSshTunnel &);

    public:
	CkSshTunnel(void);
	virtual ~CkSshTunnel(void);

	static CkSshTunnel *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	CkBaseProgress *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBaseProgress *progress);


	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// Contains an in-memory log of the listen thread. This will only contain content
	// if the KeepAcceptLog property is true.
	void get_AcceptLog(CkString &str);
	// Contains an in-memory log of the listen thread. This will only contain content
	// if the KeepAcceptLog property is true.
	const char *acceptLog(void);
	// Contains an in-memory log of the listen thread. This will only contain content
	// if the KeepAcceptLog property is true.
	void put_AcceptLog(const char *newVal);

	// Specifies a log file to be kept for the activity in the listen thread.
	void get_AcceptLogPath(CkString &str);
	// Specifies a log file to be kept for the activity in the listen thread.
	const char *acceptLogPath(void);
	// Specifies a log file to be kept for the activity in the listen thread.
	void put_AcceptLogPath(const char *newVal);

	// Maximum number of milliseconds to wait when connecting to an SSH server. The
	// default value is 10000 (i.e. 10 seconds).
	int get_ConnectTimeoutMs(void);
	// Maximum number of milliseconds to wait when connecting to an SSH server. The
	// default value is 10000 (i.e. 10 seconds).
	void put_ConnectTimeoutMs(int newVal);

	// The destination hostname or IP address (in dotted decimal notation) of the
	// service (such as a database server). Data sent through the SSH tunnel is
	// forwarded by the SSH server to this destination. Data received from the
	// destination (by the SSH server) is forwarded back to the client through the SSH
	// tunnel.
	void get_DestHostname(CkString &str);
	// The destination hostname or IP address (in dotted decimal notation) of the
	// service (such as a database server). Data sent through the SSH tunnel is
	// forwarded by the SSH server to this destination. Data received from the
	// destination (by the SSH server) is forwarded back to the client through the SSH
	// tunnel.
	const char *destHostname(void);
	// The destination hostname or IP address (in dotted decimal notation) of the
	// service (such as a database server). Data sent through the SSH tunnel is
	// forwarded by the SSH server to this destination. Data received from the
	// destination (by the SSH server) is forwarded back to the client through the SSH
	// tunnel.
	void put_DestHostname(const char *newVal);

	// The destination port of the service (such as a database server).
	int get_DestPort(void);
	// The destination port of the service (such as a database server).
	void put_DestPort(int newVal);

	// If true, then this behaves as a SOCKS proxy server for inbound connections.
	// When this property is true, the DestHostname and DestPort properties are
	// unused because the destination IP:port is dynamically provided by the SOCKS
	// client. The default value of this property is false.
	// 
	// When dynamic port forwarding is used, the InboundSocksVersion property must be
	// set to 4 or 5. If inbound SOCKS5 is used, then the InboundSocksUsername and
	// InboundSocksPassword may be set to the required login/password for a client to
	// gain access.
	// 
	bool get_DynamicPortForwarding(void);
	// If true, then this behaves as a SOCKS proxy server for inbound connections.
	// When this property is true, the DestHostname and DestPort properties are
	// unused because the destination IP:port is dynamically provided by the SOCKS
	// client. The default value of this property is false.
	// 
	// When dynamic port forwarding is used, the InboundSocksVersion property must be
	// set to 4 or 5. If inbound SOCKS5 is used, then the InboundSocksUsername and
	// InboundSocksPassword may be set to the required login/password for a client to
	// gain access.
	// 
	void put_DynamicPortForwarding(bool newVal);

	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy authentication method name. Valid choices are "Basic" or "NTLM".
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void get_HttpProxyAuthMethod(CkString &str);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy authentication method name. Valid choices are "Basic" or "NTLM".
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	const char *httpProxyAuthMethod(void);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy authentication method name. Valid choices are "Basic" or "NTLM".
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyAuthMethod(const char *newVal);

	// The NTLM authentication domain (optional) if NTLM authentication is used w/ the
	// HTTP proxy.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void get_HttpProxyDomain(CkString &str);
	// The NTLM authentication domain (optional) if NTLM authentication is used w/ the
	// HTTP proxy.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	const char *httpProxyDomain(void);
	// The NTLM authentication domain (optional) if NTLM authentication is used w/ the
	// HTTP proxy.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyDomain(const char *newVal);

	// If an HTTP proxy is to be used, set this property to the HTTP proxy hostname or
	// IPv4 address (in dotted decimal notation).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void get_HttpProxyHostname(CkString &str);
	// If an HTTP proxy is to be used, set this property to the HTTP proxy hostname or
	// IPv4 address (in dotted decimal notation).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	const char *httpProxyHostname(void);
	// If an HTTP proxy is to be used, set this property to the HTTP proxy hostname or
	// IPv4 address (in dotted decimal notation).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyHostname(const char *newVal);

	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy password.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void get_HttpProxyPassword(CkString &str);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy password.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	const char *httpProxyPassword(void);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy password.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyPassword(const char *newVal);

	// If an HTTP proxy is to be used, set this property to the HTTP proxy port number.
	// (Two commonly used HTTP proxy ports are 8080 and 3128.)
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	int get_HttpProxyPort(void);
	// If an HTTP proxy is to be used, set this property to the HTTP proxy port number.
	// (Two commonly used HTTP proxy ports are 8080 and 3128.)
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyPort(int newVal);

	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy login name.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void get_HttpProxyUsername(CkString &str);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy login name.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	const char *httpProxyUsername(void);
	// If an HTTP proxy requiring authentication is to be used, set this property to
	// the HTTP proxy login name.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through an HTTP proxy.
	// 
	void put_HttpProxyUsername(const char *newVal);

	// A tunnel will fail when progress for sending or receiving data halts for more
	// than this number of milliseconds. The default value is 10,000 (which is 10
	// seconds). A timeout of 0 indicates an infinite wait time (i.e. no timeout).
	int get_IdleTimeoutMs(void);
	// A tunnel will fail when progress for sending or receiving data halts for more
	// than this number of milliseconds. The default value is 10,000 (which is 10
	// seconds). A timeout of 0 indicates an infinite wait time (i.e. no timeout).
	void put_IdleTimeoutMs(int newVal);

	// If dynamic port forwarding is used, then this may be set to the password
	// required for authenticating inbound connections.
	void get_InboundSocksPassword(CkString &str);
	// If dynamic port forwarding is used, then this may be set to the password
	// required for authenticating inbound connections.
	const char *inboundSocksPassword(void);
	// If dynamic port forwarding is used, then this may be set to the password
	// required for authenticating inbound connections.
	void put_InboundSocksPassword(const char *newVal);

	// If dynamic port forwarding is used, then this may be set to the username
	// required for authenticating inbound connections. If no username is set, then the
	// inbound connection needs no authentication.
	void get_InboundSocksUsername(CkString &str);
	// If dynamic port forwarding is used, then this may be set to the username
	// required for authenticating inbound connections. If no username is set, then the
	// inbound connection needs no authentication.
	const char *inboundSocksUsername(void);
	// If dynamic port forwarding is used, then this may be set to the username
	// required for authenticating inbound connections. If no username is set, then the
	// inbound connection needs no authentication.
	void put_InboundSocksUsername(const char *newVal);

	// true if a background thread is running and accepting connections.
	bool get_IsAccepting(void);

	// If true, then an in-memory log of the listen thread is kept. The default value
	// is false.
	bool get_KeepAcceptLog(void);
	// If true, then an in-memory log of the listen thread is kept. The default value
	// is false.
	void put_KeepAcceptLog(bool newVal);

	// If true, then a log of the SSH tunnel thread activity is kept in memory. The
	// default value is false.
	bool get_KeepTunnelLog(void);
	// If true, then a log of the SSH tunnel thread activity is kept in memory. The
	// default value is false.
	void put_KeepTunnelLog(bool newVal);

	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the listen socket to a specific IP address (usually
	// for computers with multiple network interfaces or IP addresses). For computers
	// with a single network interface (i.e. most computers), this property should not
	// be set. For multihoming computers, the default IP address is automatically used
	// if this property is not set.
	void get_ListenBindIpAddress(CkString &str);
	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the listen socket to a specific IP address (usually
	// for computers with multiple network interfaces or IP addresses). For computers
	// with a single network interface (i.e. most computers), this property should not
	// be set. For multihoming computers, the default IP address is automatically used
	// if this property is not set.
	const char *listenBindIpAddress(void);
	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the listen socket to a specific IP address (usually
	// for computers with multiple network interfaces or IP addresses). For computers
	// with a single network interface (i.e. most computers), this property should not
	// be set. For multihoming computers, the default IP address is automatically used
	// if this property is not set.
	void put_ListenBindIpAddress(const char *newVal);

	// If a port number equal to 0 is passed to BeginAccepting, then this property will
	// contain the actual allocated port number used. Otherwise it is equal to the port
	// number passed to BeginAccepting, or 0 if BeginAccepting was never called.
	int get_ListenPort(void);

	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the socket that is to connect to the SSH server (in
	// the background thread) to a specific IP address (usually for computers with
	// multiple network interfaces or IP addresses). For computers with a single
	// network interface (i.e. most computers), this property should not be set. For
	// multihoming computers, the default IP address is automatically used if this
	// property is not set.
	void get_OutboundBindIpAddress(CkString &str);
	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the socket that is to connect to the SSH server (in
	// the background thread) to a specific IP address (usually for computers with
	// multiple network interfaces or IP addresses). For computers with a single
	// network interface (i.e. most computers), this property should not be set. For
	// multihoming computers, the default IP address is automatically used if this
	// property is not set.
	const char *outboundBindIpAddress(void);
	// In most cases, this property does not need to be set. It is provided for cases
	// where it is required to bind the socket that is to connect to the SSH server (in
	// the background thread) to a specific IP address (usually for computers with
	// multiple network interfaces or IP addresses). For computers with a single
	// network interface (i.e. most computers), this property should not be set. For
	// multihoming computers, the default IP address is automatically used if this
	// property is not set.
	void put_OutboundBindIpAddress(const char *newVal);

	// Unless there is a specific requirement for binding to a specific port, leave
	// this unset (at the default value of 0). (99.9% of all users should never need to
	// set this property.)
	int get_OutboundBindPort(void);
	// Unless there is a specific requirement for binding to a specific port, leave
	// this unset (at the default value of 0). (99.9% of all users should never need to
	// set this property.)
	void put_OutboundBindPort(int newVal);

	// Sets the receive buffer size socket option. Normally, this property should be
	// left unchanged. The default value is 0, which indicates that the receive buffer
	// size socket option should not be explicitly set (i.e. the system default value,
	// which may vary from system to system, should be used).
	// 
	// This property can be changed if download performance seems slow. It is
	// recommended to be a multiple of 4096. To see the current system's default
	// receive buffer size, examine the LastErrorText property after calling any method
	// that establishes a connection. It should be reported under the heading
	// "SO_RCVBUF". To boost performance, try setting it equal to 2, 3, or 4 times the
	// default value.
	// 
	int get_SoRcvBuf(void);
	// Sets the receive buffer size socket option. Normally, this property should be
	// left unchanged. The default value is 0, which indicates that the receive buffer
	// size socket option should not be explicitly set (i.e. the system default value,
	// which may vary from system to system, should be used).
	// 
	// This property can be changed if download performance seems slow. It is
	// recommended to be a multiple of 4096. To see the current system's default
	// receive buffer size, examine the LastErrorText property after calling any method
	// that establishes a connection. It should be reported under the heading
	// "SO_RCVBUF". To boost performance, try setting it equal to 2, 3, or 4 times the
	// default value.
	// 
	void put_SoRcvBuf(int newVal);

	// Sets the send buffer size socket option. Normally, this property should be left
	// unchanged. The default value is 0, which indicates that the send buffer size
	// socket option should not be explicitly set (i.e. the system default value, which
	// may vary from system to system, should be used).
	// 
	// This property can be changed if upload performance seems slow. It is recommended
	// to be a multiple of 4096. To see the current system's default send buffer size,
	// examine the LastErrorText property after calling any method that establishes a
	// connection. It should be reported under the heading "SO_SNDBUF". To boost
	// performance, try setting it equal to 2, 3, or 4 times the default value.
	// 
	int get_SoSndBuf(void);
	// Sets the send buffer size socket option. Normally, this property should be left
	// unchanged. The default value is 0, which indicates that the send buffer size
	// socket option should not be explicitly set (i.e. the system default value, which
	// may vary from system to system, should be used).
	// 
	// This property can be changed if upload performance seems slow. It is recommended
	// to be a multiple of 4096. To see the current system's default send buffer size,
	// examine the LastErrorText property after calling any method that establishes a
	// connection. It should be reported under the heading "SO_SNDBUF". To boost
	// performance, try setting it equal to 2, 3, or 4 times the default value.
	// 
	void put_SoSndBuf(int newVal);

	// The SOCKS4/SOCKS5 hostname or IPv4 address (in dotted decimal notation). This
	// property is only used if the SocksVersion property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void get_SocksHostname(CkString &str);
	// The SOCKS4/SOCKS5 hostname or IPv4 address (in dotted decimal notation). This
	// property is only used if the SocksVersion property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	const char *socksHostname(void);
	// The SOCKS4/SOCKS5 hostname or IPv4 address (in dotted decimal notation). This
	// property is only used if the SocksVersion property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void put_SocksHostname(const char *newVal);

	// The SOCKS5 password (if required). The SOCKS4 protocol does not include the use
	// of a password, so this does not apply to SOCKS4.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void get_SocksPassword(CkString &str);
	// The SOCKS5 password (if required). The SOCKS4 protocol does not include the use
	// of a password, so this does not apply to SOCKS4.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	const char *socksPassword(void);
	// The SOCKS5 password (if required). The SOCKS4 protocol does not include the use
	// of a password, so this does not apply to SOCKS4.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void put_SocksPassword(const char *newVal);

	// The SOCKS4/SOCKS5 proxy port. The default value is 1080. This property only
	// applies if a SOCKS proxy is used (if the SocksVersion property is set to 4 or
	// 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	int get_SocksPort(void);
	// The SOCKS4/SOCKS5 proxy port. The default value is 1080. This property only
	// applies if a SOCKS proxy is used (if the SocksVersion property is set to 4 or
	// 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void put_SocksPort(int newVal);

	// The SOCKS4/SOCKS5 proxy username. This property is only used if the SocksVersion
	// property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void get_SocksUsername(CkString &str);
	// The SOCKS4/SOCKS5 proxy username. This property is only used if the SocksVersion
	// property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	const char *socksUsername(void);
	// The SOCKS4/SOCKS5 proxy username. This property is only used if the SocksVersion
	// property is set to 4 or 5).
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void put_SocksUsername(const char *newVal);

	// SocksVersion May be set to one of the following integer values:
	// 
	// 0 - No SOCKS proxy is used. This is the default.
	// 4 - Connect via a SOCKS4 proxy.
	// 5 - Connect via a SOCKS5 proxy.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	int get_SocksVersion(void);
	// SocksVersion May be set to one of the following integer values:
	// 
	// 0 - No SOCKS proxy is used. This is the default.
	// 4 - Connect via a SOCKS4 proxy.
	// 5 - Connect via a SOCKS5 proxy.
	// 
	// Note: This is for the outbound connection to the SSH server. It is used when the
	// outbound connection to the SSH server must go through a SOCKS4 or SOCKS5 proxy.
	// 
	void put_SocksVersion(int newVal);

	// Controls whether the TCP_NODELAY socket option is used for the underlying TCP/IP
	// socket. The default value is false. Setting this property equal to true
	// disables the Nagle algorithm and allows for better performance when small
	// amounts of data are sent.
	bool get_TcpNoDelay(void);
	// Controls whether the TCP_NODELAY socket option is used for the underlying TCP/IP
	// socket. The default value is false. Setting this property equal to true
	// disables the Nagle algorithm and allows for better performance when small
	// amounts of data are sent.
	void put_TcpNoDelay(bool newVal);

	// Contains an in-memory log of the SSH tunnel thread. This will only contain
	// content if the KeepTunnelLog property is true.
	void get_TunnelLog(CkString &str);
	// Contains an in-memory log of the SSH tunnel thread. This will only contain
	// content if the KeepTunnelLog property is true.
	const char *tunnelLog(void);
	// Contains an in-memory log of the SSH tunnel thread. This will only contain
	// content if the KeepTunnelLog property is true.
	void put_TunnelLog(const char *newVal);

	// Set to keep a log file of the SSH tunnel thread.
	void get_TunnelLogPath(CkString &str);
	// Set to keep a log file of the SSH tunnel thread.
	const char *tunnelLogPath(void);
	// Set to keep a log file of the SSH tunnel thread.
	void put_TunnelLogPath(const char *newVal);

	// Set after connecting to an SSH server. The format of the fingerprint looks like
	// this: "ssh-rsa 1024 68:ff:d1:4e:6c:ff:d7:b0:d6:58:73:85:07:bc:2e:d5"
	void get_HostKeyFingerprint(CkString &str);
	// Set after connecting to an SSH server. The format of the fingerprint looks like
	// this: "ssh-rsa 1024 68:ff:d1:4e:6c:ff:d7:b0:d6:58:73:85:07:bc:2e:d5"
	const char *hostKeyFingerprint(void);



	// ----------------------
	// Methods
	// ----------------------
	// Returns true if the underlying TCP socket is connected to the SFTP server.
	bool AuthenticatePk(const char *username, CkSshKey &privateKey);

	// Returns true if the underlying TCP socket is connected to the SFTP server.
	CkTask *AuthenticatePkAsync(const char *username, CkSshKey &privateKey);


	// Authenticates with the SSH server using a login and  password.
	// 
	// An SSH session always begins by first calling Connect to connect to the SSH
	// server, and then calling either AuthenticatePw or AuthenticatePk to login.
	// 
	// Important: When reporting problems, please send the full contents of the
	// LastErrorText property to support@chilkatsoft.com.
	// Note: To learn about how to handle password change requests, see the
	// PasswordChangeRequested property (above).
	// 
	bool AuthenticatePw(const char *login, const char *password);

	// Authenticates with the SSH server using a login and  password.
	// 
	// An SSH session always begins by first calling Connect to connect to the SSH
	// server, and then calling either AuthenticatePw or AuthenticatePk to login.
	// 
	// Important: When reporting problems, please send the full contents of the
	// LastErrorText property to support@chilkatsoft.com.
	// Note: To learn about how to handle password change requests, see the
	// PasswordChangeRequested property (above).
	// 
	CkTask *AuthenticatePwAsync(const char *login, const char *password);


	// Authentication for SSH servers that require both a password and private key.
	// (Most SSH servers are configured to require one or the other, but not both.)
	// 
	// Important: When reporting problems, please send the full contents of the
	// LastErrorText property to support@chilkatsoft.com.
	// 
	bool AuthenticatePwPk(const char *username, const char *password, CkSshKey &privateKey);

	// Authentication for SSH servers that require both a password and private key.
	// (Most SSH servers are configured to require one or the other, but not both.)
	// 
	// Important: When reporting problems, please send the full contents of the
	// LastErrorText property to support@chilkatsoft.com.
	// 
	CkTask *AuthenticatePwPkAsync(const char *username, const char *password, CkSshKey &privateKey);


	// Starts a background thread for listening on listenPort. A new SSH tunnel is created
	// and managed for each accepted connection. SSH tunnels are managed in a 2nd
	// background thread: the SSH tunnel pool thread.
	// 
	// BeginAccepting starts a background thread that creates a socket, binds to the
	// port, and begins listening. If the bind fails (meaning something else may have
	// already bound to the same port), then the background thread exits. You may check
	// to see if BeginAccepting succeeds by waiting a short time (perhaps 50 millisec)
	// and then examine the IsAccepting property. If it is false, then BeginAccepting
	// failed.
	// 
	bool BeginAccepting(int listenPort);

	// Starts a background thread for listening on listenPort. A new SSH tunnel is created
	// and managed for each accepted connection. SSH tunnels are managed in a 2nd
	// background thread: the SSH tunnel pool thread.
	// 
	// BeginAccepting starts a background thread that creates a socket, binds to the
	// port, and begins listening. If the bind fails (meaning something else may have
	// already bound to the same port), then the background thread exits. You may check
	// to see if BeginAccepting succeeds by waiting a short time (perhaps 50 millisec)
	// and then examine the IsAccepting property. If it is false, then BeginAccepting
	// failed.
	// 
	CkTask *BeginAcceptingAsync(int listenPort);


	// Closes the SSH tunnel and disconnects all existing clients. If ARG1 is true,
	// the method will wait for the tunnel and client threads to exit before returning.
	bool CloseTunnel(bool waitForThreads);


	// Connects to the SSH server to be used for SSH tunneling.
	bool Connect(const char *hostname, int port);

	// Connects to the SSH server to be used for SSH tunneling.
	CkTask *ConnectAsync(const char *hostname, int port);


	// Disconnects all clients, keeping the SSH tunnel open. If ARG1 is true, the
	// method will wait for the client threads to exit before returning.
	bool DisconnectAllClients(bool waitForThreads);


	// Stops the listen background thread. It is possible to continue accepting
	// connections by re-calling BeginAccepting. If ARG1 is true, the method will
	// wait for the listen thread to exit before returning.
	bool StopAccepting(bool waitForThread);


	// Unlocks the component. This must be called once prior to calling any other
	// method. A fully-functional 30-day trial is automatically started when an
	// arbitrary string is passed to this method. For example, passing "Hello", or
	// "abc123" will unlock the component for the 1st thirty days after the initial
	// install.
	bool UnlockComponent(const char *unlockCode);


	// Connects to an SSH server through an existing SSH connection. The ARG1 is an
	// existing connected and authenticated SSH object. The connection to ARG2:ARG3 is
	// made through the existing SSH connection via port-forwarding. If successful, the
	// connection is as follows: application => ServerSSH1 => ServerSSH2. (where
	// ServerSSH1 is the ARG1 and ServerSSH2 is the SSH server at ARG2:ARG3) Once
	// connected in this way, all communications are routed through ServerSSH1 to
	// ServerSSH2. This includes authentication -- which means the application must
	// still call one of the Authenticate* methods to authenticate with ServerSSH2.
	bool ConnectThroughSsh(CkSsh &ssh, const char *hostname, int port);

	// Connects to an SSH server through an existing SSH connection. The ARG1 is an
	// existing connected and authenticated SSH object. The connection to ARG2:ARG3 is
	// made through the existing SSH connection via port-forwarding. If successful, the
	// connection is as follows: application => ServerSSH1 => ServerSSH2. (where
	// ServerSSH1 is the ARG1 and ServerSSH2 is the SSH server at ARG2:ARG3) Once
	// connected in this way, all communications are routed through ServerSSH1 to
	// ServerSSH2. This includes authentication -- which means the application must
	// still call one of the Authenticate* methods to authenticate with ServerSSH2.
	CkTask *ConnectThroughSshAsync(CkSsh &ssh, const char *hostname, int port);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
