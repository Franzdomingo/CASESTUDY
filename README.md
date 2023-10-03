# CASE STUDY

**Case Study for CS SPECIALIZATION 2 - PROGRAMMING TOOLS AND TECHNIQUES**

To run the file, you'll need to download these files.
https://ufile.io/y9b1e9nk

**Group 5**

## DOCUMENTATION REQUIREMENTS:

### Introduction:

**Purpose:**
The primary purpose of this document is to provide a comprehensive case study of Central Trust Bank’s (CTB) transformation from a traditional to a modern banking system. In-depth analysis of CTB, a financial institution with a history dating back to the early 1900s, successfully embarked on a transformative journey to align with the demands of the digital age. This case study illustrates how CTB adapted to the digital age and successfully navigated various challenges to enhance its operations, improve customer experience, and security. It serves as a guide for other financial institutions, encouraging them to navigate the complexities of a rapidly evolving financial landscape.

The scope of this document encompasses not only the transformation itself but also the broader implications and lessons from CTB’s experience. The document outlines the reasons behind this transformation, the implementation process, proposed features, and positive outcomes achieved. This document also highlights the significance of adaptability and innovation in the financial industry. By sharing CTB’s inspiring success story, this document becomes a wellspring of insights and inspiration for financial institutions worldwide, providing a practical perspective on how to adapt and lead in dynamic shifts in customer preferences and industry trends.

**Scope:**
The scope of this document encompasses a transformation of traditional banking practices. This system will streamline operations through automation, offer a unified customer portal, and a mobile banking application, enhance security with multi-factor authentication and fraud detection, enable data-driven decision-making with a data analytics dashboard, and provide 24/7 customer support through AI-driven chatbots. Importantly, it maintains the presence of physical branches and continues to cater to traditional customers while complying with regulatory standards and safeguarding customer privacy. The phased implementation approach ensures testing and refinement based on feedback, reflecting CTB’s commitment to adapt and thrive in the digital age while honoring its core values and customer needs.

**Definitions, Acronyms, and Abbreviations:**
To ensure clarity for readers, the following definitions, acronyms, and abbreviations are provided:
- CTB: Central Trust Bank
- AI: Artificial Intelligence
- Fintech: Financial Technology

**References:**
This case study is based on internal documentation, reports, and information provided by Central Trust Bank (CTB). Additionally, industry reports and relevant publications on banking and digital transformation. It does make reference to CTB’s collaboration with a fintech solutions provider, highlighting an external party’s involvement in CTB’s transformation.

### Overview:
The overview of the document begins by introducing CTB’s transformation into a modern banking institution and challenges it faced due to technological advancements. The specific problem statement and challenges are outlined, followed by the presentation of objectives for the new banking system. Proposed features, implementation process, and outcomes of the transformation are described sequentially. While the case study does not adhere to a formal structure, it expertly conveys this information and presents it systematically, ensuring a detailed understanding of CTB's successful adaptation.

## Overall Description:

### Product Perspective:
Central Trust Bank (CTB) modern banking system fits into a larger business and technological landscape as a strategic response to the evolving demands of the digital age. It is designed to align CTB with modern banking procedures and enhance its competitiveness in the financial business. This system complements CTB’s existing physical branches and traditional customer base while extending its access to more advanced technological clients via digital.

### Product Features:
- Mobile Banking Application - offers features like mobile check deposits, fund transfers, and real-time notifications for an easy on-the-go banking experience.
- Customer Portal - Customers can manage their accounts, conduct transactions, and request customer support from a single digital platform with the use of a unified customer.
- Security Protocols - Enhances security by including multi-factor authentication, encrypted transactions, and real-time fraud detection methods.
- Data Analytics Dashboard - Collects customer data, analyzes transaction patterns, and generates insights to inform business strategies and product development.
- Automated Customer Support - Uses AI-driven chatbots and virtual assistants to provide 24/7 customer support and efficiently resolve issues.

### User Classes and Characteristics:
Different types of users who might use the application and their specific needs.
- Bank Employees - Internal users that manage and monitor the digital banking system to ensure smooth operation.
- Corporate Clients - Companies that require advanced online banking services, transaction facilities, and specialized financial solutions.
- Tech-Savvy Customers - That prefer online and mobile banking, looking for quick and convenient digital services.
- Traditional Customers - That prefer in-person banking and physical branch services.

### Operating Environment:
Details on the technical environment where the application will run: OS, server details, hardware specifics.
- Server - The system handles transactions, customer data, applications logic on high-performance, and secure servers.
- Hardware - A wide range of users can access the application and it is optimized to run on standard hardware.

### Design and Implementation Constraints:
Any constraints due to system design, business policies, or external factors.
- User Experience - The system must be user-friendly and intuitive in order to accommodate clients with technological proficiency.
- Regulatory Compliance - The system must comply with banking regulations, ensuring data security, privacy, and adherence to financial laws.
- Data Security - Security must have strict protocols in order to protect customer data, to prevent unauthorized access, and lessen cybersecurity threats.

### Assumptions and Dependencies:
Any assumptions made during planning and any external factors the application depends on.
- Collaboration between CTB and fintech solutions provider for system development and integration.
- The assumption that consumers will embrace the new digital services.
- The regulatory environment has no significant changes in banking regulations that would make implementation more difficult.
- Data Availability refers to the availability of data for analysis and decision-making purposes.

## System Features and Requirements:

### Functional Requirements:

#### Registration of an Account:

**INPUT**
The user will register in the system and is required to input personal details such as fullname, username, password, email, and phone number. Subsequently, the user will be prompted to enable or disable the two-factor authentication for added security. Finally, the user should select their account type, either a savings account or a credit account.

**PROCESS**
The information provided by the user shall be securely stored within the database. In the event that the user opts to enable two-factor authentication, the security system will generate a One-Time Password (OTP) and apply encryption to the password to enhance data protection.

**OUTPUT**
The system will present the inputted personal information, including the username, email, phone number, and selected account type, within the user profile. Additionally, it will indicate whether the two-factor authentication feature is activated or deactivated.

**Account Type: Savings Account**

#### Depositing Funds:

**INPUT**
The user is required to input an amount for deposit into the banking system.

**PROCESS**
The deposited amount will be added into the user’s current balance and the transaction will be stored within the database.

**OUTPUT**
The system will display the deposited amount in the transaction page and present the current account balance on the homepage.

#### Withdrawing Funds:

**INPUT**
The user is requested to provide an amount for withdrawal within the banking system.

**PROCESS**
The withdrawn amount will be deducted from the user’s current account balance. Subsequently, the withdrawn amount will be stored in the database, facilitating accurate transaction history.

**OUTPUT**
The system will show the withdrawn amount in the transaction page

 and display the current account balance on the homepage.

**Account Type: Credit Account**

#### Making a Purchase:

**INPUT**
The user will input an amount for the purchase they are making.

**PROCESS**
The system will record in the database the details of the user’s purchase, including the corresponding amount, and subsequently deduct the user’s current balance.

**OUTPUT**
The system will display the purchase amount that the user is making and their current balance.

#### Paying Bills:

**INPUT**
The user will input the amount of money they intend to use for bill payment.

**PROCESS**
The system will record the bill payment made by the user in the database and will subsequently update their current balance by adding the payment amount.

**OUTPUT**
The system will show the bill payment being made by the user and their current balance.

#### View Transaction History:

**INPUT**
The user is only required to select the option to access the transaction history.

**PROCESS**
If the user possesses a savings account, the system will retrieve the records of deposits and withdrawals made by the user. While, if the user holds a credit account, the system will retrieve the records of purchases and bill payments executed by the user.

**OUTPUT**
The system will display the transaction history done by the user.

#### Session History:

**INPUT**
The user needs to select the option to view the session history.

**PROCESS**
The database will retrieve the records of the user logging into their account.

**OUTPUT**
The system will display the timestamps of the user’s login activities within their account.

#### Manage Account:

**INPUT**
The system allows the user to modify their password, email address, phone number, username, as well as enable or disable their two-factor authentication.

**PROCESS**
The system retrieves the password, email address, phone number, and two-factor authentication status from the database and updates them with the values inputted by the user.

**OUTPUT**
The system will display the modified values within the user’s “User Profile”.

#### Data Analytics:

**INPUT**
The user will only need to select the “Data Analytics Dashboard” option from the menu.

**PROCESS**
The system will retrieve all transactions made by the user from the database. It will then perform calculations based on the user’s account type. If the user has a savings account, the system will calculate the total net worth and total interest earned by the user. While, if the user has a credit account, the system will compute the amount spent and the amount paid by the user.

**OUTPUT**
If the user possesses a savings account, the system will display the total net worth and total interest earned by the user. While if the user holds a credit account, the system will display the amount spent and the amount paid by the user.

#### Chat with AI Assistant:

**INPUT**
The user will engage in communication with an AI assistant and may pose inquiries regarding the system.

**PROCESS**
The system will retrieve the AI assistant module and will utilize it to communicate with the user.

**OUTPUT**
The AI assistant will provide responses that are applicable to the user’s inquiries.

#### Contact:

**INPUT**
The user will select the “Contact Us” option from the menu.

**PROCESS**
The system will retrieve the contact information of the system developers that was provided.

**OUTPUT**
The system will display the contact information of the system developers.

### Non-Functional Requirements:

This section addresses the non-functional requirements of the Central Trust Bank System. Complying with these requirements is vital to guarantee the system’s efficiency, security, and design integrity, aligning it with modern banking standards.

**Performance Metrics:**
- Response Time: CTB’s modern banking system ensures that user requests, including processing transactions and inquiries are responded within a few seconds.
- Scalability: The system is designed to accommodate 50% growth in user numbers and transaction activities, without noticeable perforation deterioration.
- Availability: The system is designed to schedule maintenance downtime during off-peak hours to minimize any service interruptions.

**Security Concerns:**
- Data Security: Customer and Financial data are both encrypted during data transmission and storage. Access is restricted to authorized personnel, and regular security audits and penetration testing are done to identify and address vulnerabilities.
- Authentication and Authorization: Users undergo two-factor authentication, and access control lists are used to guarantee that users can only access data and functions relevant to their roles.

**Design Constraints:**
- Device Limitation: The system is exclusively accessible via desktops, laptops, or personal computers (PCs).
- IDE Terminal or Console: Access to the system is confined to an integrated development environment (IDE) terminal or console, providing a text-based interface for the users.
- Language Limitation: The system’s user interface and interactions are only available in the English language, limiting language support to English-speaking users.

**Standards:**
- Coding Standards: The development team uses coding conventions and best practices. They conduct code reviews to maintain code quality and readability.
- User Interface Guidelines: User interfaces are designed in accordance with industry-recognized best practices which provide a user-friendly experience.
- Performance Objectives: Performance benchmarks have been established with a set target of sustaining an average response time of fewer than 2 seconds for routine operations.

### User Interface Requirements:

The following are the mockups of the Central Trust Bank System, each accompanied by its respective description. These mockups serve to provide users with a visual representation and a clear understanding of the system’s design, layout, and functionality.

#### MAIN MENU:

**NOTE:** To provide an efficient explanation of how users should use the system, we will begin with the “Product Application”.
- Product Application: If the user is new to the system, they are required to register their account by providing the necessary information. Note: The differentiation between a savings account and a credit account lies in the transactions available to the user. Further details will be provided later.
- Login: If the user already has an existing account, they can log in directly by entering their username and password.
- Forgot Password: In case the user forgets their password, they have the option to change it.

#### Login:

When the user logs into their account, they will be greeted by the dashboard, which displays various transactions within the system.

**Transaction Center (Savings Account):** Within the transaction center, users have the option to either deposit or withdraw funds, and they can also view their transaction history.

**Transaction Center (Credit Account):** If the user possesses a credit account, they have the option to make purchases, pay bills, and view their transaction history.

#### User Profile:

In the user profile, users can access their personal details and manage them, including making modifications.

**Activity Log**
- Transaction History: It is equivalent to the transaction history found in the transaction center earlier.
- Session History: In the session history, users can view the timestamps of their logins and logouts of the system.

#### Data Analytics Dashboard:

If a user possesses a savings account, they can review their total net worth and total interest earned. If they have a credit account, they can access their total spending and total payments made.

**Help & Resources:**
In this option, users have the choice to either engage in a chat with an AI assistant for inquiries, access the contact details of the Central Trust Bank, or message the bank’s personnel.

**NOTE:** The features depicted in the following mockups pertain exclusively to the administrative and customer service staff of the Central Trust Bank system.

**Dashboard (Admin):** In the “Manage Users” option, the administrator possesses the authorization to access the data of

 all users, add new users, delete users, and update user information.

**Dashboard (Customer Service):** In the “Messages” option, the customer service staff has the ability to respond to user inquiries.

### Hardware and Software Requirements:

This explores the technical specifications required to support the Central Trust Bank system, covering both hardware and software requirements. These specifications are important for achieving optimal performance and compatibility in modern banking.

**Hardware Requirements:**
- Server Infrastructure: High-performance servers with sufficient processing capabilities and memory requirements to effectively manage the system’s computational demands.
- Data Storage: Scalable and secure data storage solutions, and database servers, for storing user and transaction data.
- Devices: Ensuring compatibility with a diverse range of personal computers, desktops, and laptops to accommodate the varying device preferences of the users.

**Software Requirements:**
- Application Development Frameworks: Utilization of development frameworks and technologies to create the banking system and data analytics dashboard.
- AI Chatbot Frameworks: Integrating AI and chatbot framework to create AI virtual assistants.
- Database Management System: Connecting in a secure database management system to manage and store user data.
- Security Software: Implementation of security software for two-factor authentication and encryption.
- Analytics Tools: Using data analytics tools to create the data analytics dashboard by facilitating the collection of customer data and the generation of insights.
- Customer Support Integration: Integrating customer support and communication tools to enable the functionality of AI chatbot assistant.

### Data Management or Database Requirements:

This section discusses the considerations that the Central Trust Bank system must address to ensure efficient data storage, retrieval, and security. Additionally, it covers the integration of data analytics tools and the importance of adhering to essential security protocols.

- Scalable Data Storage: Establishing a data storage that is scalable and can accommodate an increasing volume of user data, transaction records, and analytical data from the system.
- Data Retrieval: Enabling efficient data retrieval for functionalities such as transaction processing, account management, and data analytics.
- Data Security: Using encryption to secure financial data.
- Data Analytics Integration: Integrating data analytics tools with the database system for the feature data analytics dashboard.
- Integration with Security Protocols: Using two-factor authentication and encryption to protect sensitive data stored in the database.

### System Models:

This presents the Entity Relationship Diagrams (ERDs) created to illustrate the structure and relationships within the Central Trust Bank system. These visual representations facilitate a deeper understanding of how the system works and its features.

### TESTING

(End of README.md)
