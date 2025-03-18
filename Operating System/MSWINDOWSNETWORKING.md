# Microsoft Windows - Networking Capabilities

Microsoft Windows has extensive networking capabilities, supporting both peer-to-peer and client–server networking, along with facilities for network management. The networking components in Windows provide data transport, interprocess communication, file sharing across a network, and the ability to send print jobs to remote printers.

## Internal Networking Interfaces

### Windows utilizes two key internal networking interfaces

- **Network Device Interface Specification (NDIS)**: Developed by Microsoft and 3Com in 1989, NDIS separates network adapters from transport protocols, allowing either to be changed without affecting the other. It resides between the data-link and network layers of the OSI model and enables multiple protocols to operate over various network adapters.

- **Transport Driver Interface (TDI)**: TDI acts as the interface between the transport layer (layer 4) and the session layer (layer 5) of the OSI model. It allows any session-layer component to use any available transport mechanism, supporting both connection-based and connectionless transport and offering functions to send any type of data. A similar reasoning led to the streams mechanism in UNIX.

## Networking Protocols

Windows implements transport protocols as drivers that can be loaded and unloaded dynamically, although a system reboot is often required after a change. Several networking protocols are included with Windows:

- **Server Message Block (SMB):** Introduced in MS-DOS 3.1, SMB is used to send I/O requests over the network. It has four message types:

  - Session control messages (start and end redirector connections to shared server resources).

  - File messages (access files on the server).

  - Printer messages (send data to remote print queues and receive status).

  - Message messages (communicate with other workstations). A version of SMB, the Common Internet File System (CIFS), is supported on various operating systems. Windows uses CIFS servers.

- **Transmission Control Protocol/Internet Protocol (TCP/IP):** The de facto standard networking infrastructure used on the Internet. Windows uses TCP/IP to connect to a wide range of operating systems and hardware platforms. The Windows TCP/IP package includes Simple Network Management Protocol (SNMP), Dynamic Host Configuration Protocol (DHCP), and Windows Internet Name Service (WINS). Windows Vista introduced a TCP/IP implementation supporting both IPv4 and IPv6 in the same network stack, along with the offloading of the network stack onto advanced hardware for high performance on servers. Windows also includes a software firewall to limit the TCP ports programs can use for network communication, enhancing security.

- **Point-to-Point Tunneling Protocol (PPTP):** A protocol provided by Windows for communication between remote-access server modules on Windows Server machines and client systems connected over the Internet. Remote-access servers can encrypt data and support multiprotocol Virtual Private Networks (VPNs).

- **HTTP Protocol:** Used for getting and putting information on the World Wide Web. Windows implements HTTP using a kernel-mode driver, allowing web servers to operate with low overhead. HTTP is also available as a transport option for implementing Remote Procedure Calls (RPC).

- **Web-Distributed Authoring and Versioning Protocol (WebDAV):** An HTTP-based protocol for collaborative authoring across a network. Windows integrates a WebDAV redirector into the file system, enabling it to work with other file-system features like encryption. This allows secure storage of personal files in public locations, with local caching due to HTTP's get/put nature.

- **Named Pipes:** A connection-oriented messaging mechanism for communication between processes on the same machine. Accessed through the file-system interface, they inherit file object security mechanisms. The SMB protocol supports named pipes, enabling inter-system communication as well.

- **Remote Procedure Calls (RPCs):** Client–server mechanisms enabling an application on one machine to make a procedure call to code on another. A client stub packs arguments into a message and sends it across the network to a server process, then blocks. The server unpacks the message, calls the procedure, packs results, and sends them back to the client stub, which unblocks and returns the results. This packing is called marshaling, and the necessary code is compiled from a Microsoft Interface Definition Language specification. Windows RPC follows the distributed-computing-environment standard, ensuring portability by specifying standard data formats to hide architectural differences. RPC uses multiple transports, such as named pipes and TCP/IP, for inter-system communication.

- **Component Object Model (COM):** A mechanism for interprocess communication in Windows, providing well-defined interfaces to manipulate object data. Used by technologies like Object Linking and Embedding (OLE). A distributed extension, DCOM, utilizes RPC over a network for transparent distributed application development.

## Client-Server Model

Windows extensively uses the client–server model, both internally and for networking. Environment subsystems and Windows user-mode services are implemented as processes communicating with clients via RPC. This architecture provides a suitable base for distributed computing. Local servers can forward messages to remote servers on behalf of local clients, with clients unaware of whether a request is serviced locally or remotely. The choice can even change dynamically based on load and configuration. For implementing client–server computing, RPCs are the recommended paradigm due to their security, serialization services, and extensibility. When RPC occurs locally, the Advanced Local Procedure Call (ALPC) facility can be used as a more optimized transport.

## Redirectors and Servers

Windows allows applications to access remote files as if they were local, provided the remote computer runs a CIFS server. A redirector on the client side forwards I/O requests to a remote server, which satisfies them. Redirectors and servers operate in kernel mode for performance and security. The process involves the redirector sending a network request, remote network drivers passing it to the server driver, which then interacts with the local file-system and device drivers to access data, and the results are sent back through the server driver and redirector to the application via the I/O manager. A similar process occurs with the Win32 network API using a multi-provider router instead of a MUP.

## Domains

Windows uses the concept of a domain to manage global access rights within groups of users in networked environments. While previously unrelated to the Domain Name System (DNS), they are now closely linked.

## Programmer Interface (Win32 API)

The Win32 API provides the fundamental interface to Windows networking capabilities. Winsock (Windows Sockets API) is a key component, providing a session-layer interface largely compatible with UNIX sockets but with Windows extensions. It offers a standardized interface to various transport protocols with potentially different addressing schemes, allowing Winsock applications to run on any Winsock-compliant protocol stack. Winsock follows the Windows Open System Architecture (WOSA) model, offering a standard service provider interface (SPI) between applications and networking protocols, enabling the loading and unloading of layered protocols for added functionality like security. It supports asynchronous operations, notifications, reliable multicasting, secure sockets, and kernel-mode sockets, along with simpler usage models like WSAConnectByName().

## Security Considerations

Windows aims to be secure by default. The built-in software firewall is an important security measure, limiting the TCP ports programs can use for network communication. The security of network communication is a general concern, as networked computers receive bits without a reliable way to determine the sender, and sending computers don't know who might receive them or if eavesdropping occurs. Network addresses are commonly used to infer senders and receivers, but source addresses can be falsified.

## Windows 7 Networking

Windows 7 also supports both peer-to-peer and client–server networking with similar functionalities for data transport, interprocess communication, file sharing, and remote printing. It utilizes NDIS and TDI interfaces and includes protocols like SMB, TCP/IP, PPTP, HTTP, WebDAV, and named pipes. Windows 7 also implements RPC following the same distributed-computing-environment standard and uses redirectors and servers for accessing remote files. The Win32 API and Winsock provide the programmer interface for networking in Windows 7 as well. Windows 7 uses domains for managing access rights.

## Feature Migration

The sources highlight that features initially found in larger systems often migrate to smaller ones. Networking capabilities, initially prevalent in mainframe and minicomputer operating systems, have become fundamental to microcomputer and even embedded operating systems like Windows.
