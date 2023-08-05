#ifndef MYFILE_H
#define MYFILE_H

class myFile{
	private:
		char *name;
	public:
		myFile();
		myFile(char*);
	 	void setName(char *);
		char *getName();
		bool exists() const;
		int countLines() const;
		int countChars() const;
		myFile operator=(const myFile &);
		myFile &operator+=(const myFile &);
		friend bool operator==(const myFile &,const myFile &);
};

#endif //MYFILE_H