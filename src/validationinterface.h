/*
 * This file is part of the Flowee project
 * Copyright (C) 2009-2010 Satoshi Nakamoto
 * Copyright (C) 2009-2015 The Bitcoin Core developers
 * Copyright (C) 2017 Tom Zander <tomz@freedommail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITCOIN_VALIDATIONINTERFACE_H
#define BITCOIN_VALIDATIONINTERFACE_H

#include <boost/signals2/signal.hpp>
#include <boost/shared_ptr.hpp>

class CBlock;
struct CBlockLocator;
class CBlockIndex;
class CReserveScript;
class CTransaction;
class CValidationInterface;
class CValidationState;
class uint256;

// These functions dispatch to one or all registered wallets

/** Register a wallet to receive updates from core */
void RegisterValidationInterface(CValidationInterface* pwalletIn);
/** Unregister a wallet from core */
void UnregisterValidationInterface(CValidationInterface* pwalletIn);
/** Unregister all wallets from core */
void UnregisterAllValidationInterfaces();
/** Push an updated transaction to all registered wallets */
void SyncWithWallets(const CTransaction& tx, const CBlock* pblock = NULL);
/** Push an updated transaction to all registered wallets */
void SyncBlockWithWallets(const CBlock* pblock);

class CValidationInterface {
protected:
    virtual void UpdatedBlockTip(const CBlockIndex *pindex) {}
    virtual void SyncTransaction(const CTransaction &tx, const CBlock *pblock) {}
    virtual void SyncAllTransactionsInBlock(const CBlock *pblock) {}
    virtual void SetBestChain(const CBlockLocator &locator) {}
    virtual void UpdatedTransaction(const uint256 &hash) {}
    virtual void Inventory(const uint256 &hash) {}
    virtual void ResendWalletTransactions(int64_t nBestBlockTime) {}
    virtual void BlockChecked(const CBlock&, const CValidationState&) {}
    virtual void GetScriptForMining(boost::shared_ptr<CReserveScript>&) {}
    virtual void ResetRequestCount(const uint256 &hash) {}
    friend void ::RegisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterValidationInterface(CValidationInterface*);
    friend void ::UnregisterAllValidationInterfaces();
};

struct CMainSignals {
    /** Notifies listeners of updated block chain tip */
    boost::signals2::signal<void (const CBlockIndex *)> UpdatedBlockTip;
    /** Notifies listeners of updated transaction data, and optionally the block it is found in. */
    boost::signals2::signal<void (const CTransaction &, const CBlock *)> SyncTransaction;
    /** Notifies listeners of updated transaction data, on a new accepted block. */
    boost::signals2::signal<void (const CBlock *)> SyncAllTransactionsInBlock;
    /** Notifies listeners of an updated transaction without new data (for now: a coinbase potentially becoming visible). */
    boost::signals2::signal<void (const uint256 &)> UpdatedTransaction;
    /** Notifies listeners of a new active block chain. */
    boost::signals2::signal<void (const CBlockLocator &)> SetBestChain;
    /** Notifies listeners about an inventory item being seen on the network. */
    boost::signals2::signal<void (const uint256 &)> Inventory;
    /** Tells listeners to broadcast their data. */
    boost::signals2::signal<void (int64_t nBestBlockTime)> Broadcast;
    /** Notifies listeners of a block validation result */
    boost::signals2::signal<void (const CBlock&, const CValidationState&)> BlockChecked;
    /** Notifies listeners that a key for mining is required (coinbase) */
    boost::signals2::signal<void (boost::shared_ptr<CReserveScript>&)> ScriptForMining;
    /** Notifies listeners that a block has been successfully mined */
    boost::signals2::signal<void (const uint256 &)> BlockFound;
};

CMainSignals& GetMainSignals();

#endif // BITCOIN_VALIDATIONINTERFACE_H
