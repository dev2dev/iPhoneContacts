/*
 * ABAddressBook.h
 * iPhoneContacts
 * 
 * Created by Jim Dovey on 5/6/2009.
 * 
 * Copyright (c) 2009 Jim Dovey
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#import <Foundation/Foundation.h>
#import <AddressBook/ABAddressBook.h>
#import "ABRefInitialization.h"

@class ABRecord, ABPerson, ABGroup, ABSource;
@protocol ABAddressBookDelegate;

enum
{
    ABOperationNotPermittedByStoreError = kABOperationNotPermittedByStoreError
    
};

@interface ABAddressBook : NSObject <ABRefInitialization>
{
    ABAddressBookRef            _ref;
    id<ABAddressBookDelegate>   _delegate;
}

+ (ABAddressBook *) sharedAddressBook;

@property (nonatomic, readonly, getter=getAddressBookRef) ABAddressBookRef addressBookRef;

@property (nonatomic, assign) id<ABAddressBookDelegate> delegate;

- (BOOL) save: (NSError **) error;
@property (nonatomic, readonly) BOOL hasUnsavedChanges;

- (BOOL) addRecord: (ABRecord *) record error: (NSError **) error;
- (BOOL) removeRecord: (ABRecord *) record error: (NSError **) error;

- (NSString *) localizedStringForLabel: (NSString *) labelName;

- (void) revert;

@end

@interface ABAddressBook (People)

@property (nonatomic, readonly) NSUInteger personCount;

- (ABPerson *) personWithRecordID: (ABRecordID) recordID;
- (NSArray *) allPeople;
- (NSArray *) allPeopleSorted;
- (NSArray *) allPeopleWithName: (NSString *) name;

@end

@interface ABAddressBook (Groups)

@property (nonatomic, readonly) NSUInteger groupCount;

- (ABGroup *) groupWithRecordID: (ABRecordID) recordID;
- (NSArray *) allGroups;

@end

@interface ABAddressBook (Sources)

- (ABSource *) sourceWithRecordID: (ABRecordID) recordID;
- (ABSource *) defaultSource;
- (NSArray *) allSources;

@end

@protocol ABAddressBookDelegate <NSObject>
- (void) addressBookDidChange: (ABAddressBook *) addressBook;
@end
